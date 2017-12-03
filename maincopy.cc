#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
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



class InvalidCmd{};
Level *setLevel(int n, const string &s);


void read_cmd(string &command, Board *b, Level *level, const string &seed, bool &on_block_seq) {
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
		bool result = b->drop();
		if (result == false) {
			command = "restart";
			read_cmd(command, b, level, seed, on_block_seq);
		}
	} else if (command == "levelup") {
		int levelnum = level->getLevelNum();
		delete level;
		levelnum++;
		level = setLevel(levelnum, seed);
		b->updateState();
		b->notifyObservers();
		if (level->getLevelNum() == 1) on_block_seq = false;
	} else if (command == "leveldown") {
		int levelnum = level->getLevelNum();
		delete level;
		levelnum--;
		level = setLevel(levelnum, seed);
		b->updateState();
		b->notifyObservers();
		if (level->getLevelNum() == 0) on_block_seq = true;
		if (level->getLevelNum() == 2) on_block_seq = false;
	} else if (command == "I" || command == "J" || command == "L" || 
		command == "O" || command == "S" || command == "T" || command == "Z") {
		BlockType blockt = str_transform(command);
		b->generateBlock(blockt, level->getLevelNum());
	} else if (command == "restart") {
		b->init(level);
//	} else if (command == "hint") {
//		b->hint();
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
	//I,J,L...........
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
	for (int i = 1; i < argc; i++) {
		string flag = argv[i];
		if (flag == "-text") {
			graphic = false;
		} else if (flag == "-seed") {
			seed = argv[i+1];
		} else if (flag == "-scriptfile") {
			block_seq = argv[i+1];
		} else if (flag == "-startlevel") {
			string string_for_iss = argv[i+1];
			istringstream iss{string_for_iss};
			iss >> levelnum; 
			if (levelnum != 0) {
				on_block_seq = false;
			}
		}
	}
	Level *level= setLevel(levelnum, seed);
	b.init(level);
	TextDisplay *td = new TextDisplay{b.getWidth(), b.getHeight(), levelnum, 0, 0}; 
	b.attach(td);
	GraphicsDisplay *gd = nullptr;
	if (graphic) {
		gd = new GraphicsDisplay{b.getWidth(), b.getHeight(), levelnum, 0, 0};
		b.attach(gd);
	}
	bool newgame = true;
	vector<pair<string, string>> cmd_names = starting_cmds();
	string command;
	int times = 0;
//	bool last_hint = false;
	while (1) {
		try{
			if (newgame) {
				cout << b;
				if (on_block_seq) {
					string next_blockt;
					iff_block_seq >> next_blockt;
					if (iff_block_seq.eof()) {
						cout << "Run out off blocks. Game over." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
					blockt = str_transform(next_blockt);
					b.generate(blockt, level->getLevelNum());
					iff_block_seq >> next_blockt;
					if (iff_block_seq.eof()) {
						cout << "Run out off blocks. Game over." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
					blockt = str_transform(next_blockt);
					b.generate(blockt, level->getLevelNum());
				} else {
					b.generate();
					b.generate();
				}
			}
//		if (last_hint) {
//			b.clearHint();
//			last_hint = false;
//		}
			if (times == 0) {
				cout << b;
				if (on_command_seq) {
					iff_command_seq >> command;
					if (iff_command_seq.eof()) { 
						cout << "Run out of commands. Game over." << endl;
						delete level;
						delete td;
						delete gd;
						break;
					}
				} else {
					cin >> command;
					if (cin.fail()) {
						cout << "Run out of commands. Game over." << endl;
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
			if (command == "restart" || command == "hint" || 
				command == "norandom" || command == "random") {
				times = 1;
		}
		if (command == "giveup") {
			cout << "Game over." << endl;
			times--;
			delete level;
			delete td;
			delete gd;
			break;
		}
		if (command == "sequence") {
			if (on_command_seq) {
				iff_command_seq >> command_seq;
			} else {
				cin >> command_seq;
			}
			on_command_seq = true;
			iff_command_seq = ifstream{command_seq};
			times--;
		} else if (command == "nonrandom") {
			if (level->getLevelNum() == 3 || level->getLevelNum() == 4) {
				if (on_block_seq) {
					iff_block_seq >> block_seq;
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
		} else {
			for (int i = 0; i < times; i++) {
				read_cmd(command, &b, level, seed, on_block_seq);
				if (command == "drop" || command == "restart") {
					if (command == "restart") {
						delete td;
						td = new TextDisplay{b.getWidth(), b.getHeight(), level->getLevelNum(), 0, b.getHiScore()};
						b.attach(td);
						if (graphic) {
							delete gd;
							gd = new GraphicsDisplay{b.getWidth(), b.getHeight(), level->getLevelNum(), 0, b.getHiScore()};
							b.attach(gd);
						}
					}
					if (on_block_seq) {
						string next_blockt;
						iff_block_seq >> next_blockt;
						if (iff_block_seq.eof()) {
							cout << "Run out off blocks. Game over.";
							delete level;
							delete td;
							delete gd;
							break;
						}
						blockt = str_transform(next_blockt);
						b.generate(blockt, level->getLevelNum());
						if (command == "restart") {
							iff_block_seq >> next_blockt;
							if (iff_block_seq.eof()) {
								cout << "Run out off blocks. Game over.";
								delete level;
								delete td;
								delete gd;
								break;
							}
							blockt = str_transform(next_blockt);
							b.generate(blockt, level->getLevelNum());
							times = 0;
						}
					} else {
						b.generate();
						if (command == "restart") {
							b.generate();
							times = 0;
						}
					}
				} 
				// else if (command == "hint") last_hint = true;
			}
			if (moving_cmd(command)) {
				b.heavy();
			}
			times = 0;
		}
	}
	catch (InvalidCmd e) {
		cout << command << " is invalid. Please try again." << endl;
		times = 0;
	}
}
}
