#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "board.h"
#include "levelzero.h"
#include "level.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "blocktype.h"

using namespace std;


class InvalidCmd{};
Level *setLevel(int n, const string &s);


void read_cmd(string &command, Board *b, Level **level, const string &seed, bool &on_block_seq) {
	if (command == "left") {
		b->left();
	} else if (command == "right") {
		b->right();
	} else if (command == "down") {
		b->down();
	} else if (command == "clockwise") {
		b->clock();
	} else if (command == "counterclockwise") {
		b->coclock();
	} else if (command == "drop") {
		b->drop();
	} else if (command == "levelup") {
		int levelnum = (*level)->getLevelNum();
		if(*level) delete *level;
		levelnum++;
		*level = setLevel(levelnum, seed);
		b->setLevel(*level);
		b->updateState();
		b->notifyObservers();
		cout << (*level)->getLevelNum()<<endl;
		if (levelnum == 1) on_block_seq = false;
	} else if (command == "leveldown") {
		int levelnum = (*level)->getLevelNum();
		if(*level) delete *level;
		levelnum--;
		*level = setLevel(levelnum, seed);
		b->setLevel(*level);
		b->updateState();
		b->notifyObservers();
		if (levelnum == 0) on_block_seq = true;
		if (levelnum == 2) on_block_seq = false;
	} else if (command == "hint") {
		b->giveHint();
	}
}



bool moving_cmd(const string &command) {
	if (command == "left" || command == "right" || command == "down" || 
		command == "clockwise" || command == "counterclockwise") {
		return true;
} else {
	return false;
}
}

vector<pair<string, string>> starting_cmds() {
	vector<pair<string, string>> vec;
	vec.emplace_back(pair<string, string>("left", "left"));
	vec.emplace_back(pair<string, string>("right", "right"));
	vec.emplace_back(pair<string, string>("down", "down"));
	vec.emplace_back(pair<string, string>("clockwise", "clockwise"));
	vec.emplace_back(pair<string, string>("counterclockwise", "counterclockwise"));
	vec.emplace_back(pair<string, string>("drop", "drop"));
	vec.emplace_back(pair<string, string>("levelup", "levelup"));
	vec.emplace_back(pair<string, string>("leveldown", "leveldown"));
	vec.emplace_back(pair<string, string>("norandom", "norandom"));
	vec.emplace_back(pair<string, string>("random", "random"));
	vec.emplace_back(pair<string, string>("sequence", "sequence"));
	vec.emplace_back(pair<string, string>("I", "I"));
	vec.emplace_back(pair<string, string>("J", "J"));
	vec.emplace_back(pair<string, string>("L", "L"));
	vec.emplace_back(pair<string, string>("O", "O"));
	vec.emplace_back(pair<string, string>("T", "T"));
	vec.emplace_back(pair<string, string>("S", "S"));
	vec.emplace_back(pair<string, string>("Z", "Z"));
	vec.emplace_back(pair<string, string>("restart", "restart"));
	vec.emplace_back(pair<string, string>("hint", "hint"));
	vec.emplace_back(pair<string, string>("rename", "rename"));
	vec.emplace_back(pair<string, string>("giveup", "giveup"));
	return vec;
}

string actual_cmd(const string &command, const vector<pair<string, string>> &cmd_names) {
	for (int i = 0; i < cmd_names.size(); i++) {
		bool same = true;
		string curr_cmd = cmd_names[i].first;
		for (int j = 0; j < command.length(); j++) {
			if (curr_cmd[j] != command[j]) {
				same = false;
				break;
			}
		}
		if (same) {
			return cmd_names[i].second;
		}
	}
	throw InvalidCmd{};
} 

Level *setLevel(int n, const string &s) {
	if (s == "") {
		if (n <= 0) {
			Level *new_level = new LevelZero{-1, false};
			return new_level;
		} else if (n == 1) {
			Level *new_level = new LevelOne{-1, false};
			return new_level;
		} else if (n == 2) {
			Level *new_level = new LevelTwo{-1, false};
			return new_level;
		} else if (n == 3) {
			Level *new_level = new LevelThree{-1, false};
			return new_level;
		} else {
			Level *new_level = new LevelFour{-1, false};
			return new_level;
		}
	} else {
		istringstream iss{s};
		int seed;
		iss >> seed;
		if (n <= 0) {
			Level *new_level = new LevelZero{seed, true};
			return new_level;
		} else if (n == 1) {
			Level *new_level = new LevelOne{seed, true};
			return new_level;
		} else if (n == 2) {
			Level *new_level = new LevelTwo{seed, true};
			return new_level;
		} else if (n == 3) {
			Level *new_level = new LevelThree{seed, true};
			return new_level;
		} else {
			Level *new_level = new LevelFour{seed, true};
			return new_level;
		}
	}
}


void rename_cmd(vector<pair<string, string>> &cmd_names, const string &old_cmd, const string &new_cmd) {
	bool exist = false;
	string actual_old = actual_cmd(old_cmd, cmd_names);
	for (int i = 0; i < cmd_names.size(); i++) {
		exist = true;
		if (actual_old == cmd_names[i].first) {
			cmd_names[i].first = new_cmd;
		}
	}
	if (!exist) throw InvalidCmd{};
}


int main(int argc, char *argv[]) {
	Board b;
	string seed = "";
	int levelnum = 0;
	string block_seq = "sequence.txt";
	bool on_block_seq = true;
	ifstream iff_block_seq{block_seq};
	string command_seq = "";
	bool on_command_seq = false;
	ifstream iff_command_seq{command_seq};
	BlockType blockt = BlockType::None;
	bool graphic = true;
	bool script = false;
	for (int i = 1; i < argc; i++) {
		string flag = argv[i];
		if (flag == "-text") {
			graphic = false;
		} else if (flag == "-seed") {
			seed = argv[i+1];
		} else if (flag == "-scriptfile") {
			block_seq = argv[i+1];
			script = true;
			iff_block_seq = ifstream{block_seq};
		} else if (flag == "-startlevel") {
			string string_for_iss = argv[i+1];
			istringstream iss{string_for_iss};
			iss >> levelnum; 
			if (levelnum >= 0 && !script) {
				on_block_seq = false;
			}
		}
	}
	Level *level= setLevel(levelnum, seed);
	TextDisplay *td = new TextDisplay{b.getWidth(), b.getHeight(), level->getLevelNum(), 0, 0}; 
	b.attach(td);
	GraphicsDisplay *gd = nullptr;
	if (graphic) {
		gd = new GraphicsDisplay{b.getWidth(), b.getHeight(), level->getLevelNum(), 0, 0};
		b.attach(gd);
	}
	b.init(level);
	bool newgame = true;
	vector<pair<string, string>> cmd_names = starting_cmds();
	string command;
	int times = 0;
	bool last_hint = false;
	while (1) {
		try{
			if (newgame) {
				newgame = false;
				if (on_block_seq) {
					string next_blockt;
					iff_block_seq >> next_blockt;
					if (iff_block_seq.eof()) {
						cout << "Run out off blocks. Game over." << endl;
						command = "restart";
						continue;
					}
					blockt = str_transform(next_blockt);
					if (!b.generate(blockt, level->getLevelNum())){
						cout << "Game over." << endl;
						command = "restart";
						continue;
					}
					iff_block_seq >> next_blockt;
					if (iff_block_seq.eof()) {
						cout << "Run out off blocks. Game over." << endl;
						command = "restart";
						continue;
					}
					blockt = str_transform(next_blockt);
					if (!b.generate(blockt, level->getLevelNum())){
						cout << "Game over." << endl;
						command = "restart";
						continue;
					}
					cout << b;
					times = 0;
				} else {
					if (!b.generate()){
						cout << "Game over." << endl;
						command = "restart";
						continue;
					}
					if (!b.generate()){
						cout << "Game over." << endl;
						command = "restart";
						continue;
					}
					cout << b;
					times = 0;
				}
			}
			if (command == "hint") {
				b.clearHint();
			}
			if (times == 0) {
				if (on_command_seq) {
					iff_command_seq >> command;
					if (iff_command_seq.eof()) { 
						cout << "Run out of commands. Game over." << endl;
						cout << "Window closed." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
				} else {
					cin >> command;
					if (cin.fail()) {
						cout << "Run out of commands. Game over." << endl;
						cout << "Window closed." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
				}
				string str_times = command.substr(0, 1);
				int temp_times;
				istringstream iss_times{str_times};
				if (iss_times >> temp_times) {
					times = temp_times;
					command = command.substr(1);
				} else {
					times = 1;
				}
				command = actual_cmd(command, cmd_names);
			}
			if (command == "restart" || command == "hint" || command == "norandom" || 
				command == "random" || command == "rename") {
				times = 1;
			}
			if (command == "giveup") {
				cout << "Game over." << endl;
				cout << "Window closed." << endl;
				delete level;
				delete td;
				delete gd;
				break;
			}
			if (command == "rename") {
				string old_cmd;
				string new_cmd;
				if (on_command_seq) {
					iff_command_seq >> old_cmd;
					if (iff_command_seq.eof()) { 
						cout << "Run out of commands. Game over." << endl;
						cout << "Window closed." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
					iff_command_seq >> new_cmd;
					if (iff_command_seq.eof()) { 
						cout << "Run out of commands. Game over." << endl;
						cout << "Window closed." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
					rename_cmd(cmd_names, old_cmd, new_cmd);
				} else {
					cin >> old_cmd;
					if (cin.fail()) { 
						cout << "Run out of commands. Game over." << endl;
						cout << "Window closed." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
					cin >> new_cmd;
					if (iff_command_seq.eof()) { 
						cout << "Run out of commands. Game over." << endl;
						cout << "Window closed." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
					rename_cmd(cmd_names, old_cmd, new_cmd);
				}
				times--;
			}
			if (command == "sequence") {
				if (on_command_seq) {
					iff_command_seq >> command_seq;
					if (iff_command_seq.eof()) { 
						cout << "Run out of commands. Game over." << endl;
						cout << "Window closed." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
				} else {
					cin >> command_seq;
				}
				on_command_seq = true;
				iff_command_seq = ifstream{command_seq};
				times--;
			} else if (command == "norandom") {
				if (level->getLevelNum() == 3 || level->getLevelNum() == 4) {
					if (on_command_seq) {
						iff_command_seq >> block_seq;
						if (iff_command_seq.eof()) { 
							cout << "Run out of commands. Game over." << endl;
							cout << "Window closed." << endl;
							delete level;
							delete td;
							delete gd;
							break;
						}
					} else {
						cin >> block_seq;
					}
					on_block_seq = true;
					iff_block_seq = ifstream{block_seq};
					times--;
				} else {
					throw InvalidCmd{};
				}
			} else if (command == "random") {
				if (level->getLevelNum() == 3 || level->getLevelNum() == 4) {
					on_block_seq = false;
					times--;
				} else {
					throw InvalidCmd{};
				}
			} else if (command == "restart") {
				cout << "Game over." << endl;
				b.detach(td);
				b.detach(gd);
				delete td;
				td = new TextDisplay{b.getWidth(), b.getHeight(), level->getLevelNum(), 0, b.getHiScore()};
				b.attach(td);
				if (graphic) {
					GraphicsDisplay *temp = gd;
					gd = new GraphicsDisplay{b.getWidth(), b.getHeight(), level->getLevelNum(), 0, b.getHiScore()};
					delete temp;
					b.attach(gd);
				}
				b.init(level);
				newgame = true;
				if (on_block_seq) {
					iff_block_seq = ifstream{block_seq};
				}
			} else if (command == "I" || command == "J" || command == "L" || 
				command == "O" || command == "S" || command == "T" || command == "Z") {
				BlockType blockt = str_transform(command);
				if (!b.generateBlock(blockt, level->getLevelNum())){
					cout << "Game over."<<endl;
					command = "restart";
				}
				times--;
			} else {
				for (int i = 0; i < times; i++) {
					read_cmd(command, &b, &level, seed, on_block_seq);
					if (command == "drop" || command == "restart") {
						if (on_block_seq) {
							string next_blockt;
							iff_block_seq >> next_blockt;
							if (iff_block_seq.eof()) {
								command = "restart";
								break;
							}
							blockt = str_transform(next_blockt);
							if (!b.generate(blockt, level->getLevelNum())){
								//cout << "whynot"<<endl;
								command = "restart";
								break;
							}
							cout << "whynot"<<endl;
						} else {
							if (!b.generate()){
								command = "restart";
								break;
							}
						}
					} 
				if (command == "hint") last_hint = true;
				}
				if (moving_cmd(command)) {
					b.heavy();
				}
				if (command != "restart") times = 0;
			}
			if (times == 0) cout << b;
		}
		catch (InvalidCmd e) {
			cout << command << " is invalid. Please try again." << endl;
			times = 0;
		}
	}
}
