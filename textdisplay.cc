#include "state.h"
#include "cellstate.h"
#include "blockstate.h"
#include "gamestate.h"
#include "cell.h"
#include "textdisplay.h"

using namespace std;

void TextDisplay::nextClear() {
	for (int i = 0; i < next_h; i++) {
		for (int j = 0; j < next_w; j++) {
			next[i][j] = ' ';
		}
	}
}


void TextDisplay::currClear() {
	for (int i = 0; i < curr.size(); i++) {
		int index_r = curr[i].first;
		int index_c = curr[i].second;
		textDis[index_r][index_c] = ' ';
	}
	curr.clear();
	clearcurr = true;
}


TextDisplay::TextDisplay(int width, int height,int level, int score, int hiscore): 
width{width}, height{height}, level{level}, score{score}, hiscore{hiscore} {
	clearcurr = true;
	next_w = 4;
	next_h = 2;
	for (int i = 0; i < height; i++) {
		vector<char> row;
		for (int j = 0; j < width; j++) {
			row.emplace_back(' ');
		}
		textDis.emplace_back(row);
	}
	for (int i = 0; i < next_h; i++) {
		vector<char> row;
		for (int j = 0; j < next_w; j++) {
			row.emplace_back(' ');
		}
		next.emplace_back(row);
	}
}


void TextDisplay::notify(Subject &whoNotified) {
	State *state = whoNotified.getState();
	GameState *gs = dynamic_cast<GameState *>(state);
	if (gs) {
		level = gs->level;
		hiscore = gs->hiscore;
		score = gs->score;
	} else {
		CellState *cs = dynamic_cast<CellState *>(state);
		if (cs) {
			if (!clearcurr) currClear();
				int index_r = cs->r;
				int index_c = cs->c;
				BlockType bt = cs->blockt;
				textDis[index_r][index_c] = transform_char(bt);
		} else {
			BlockState *bs = dynamic_cast<BlockState *>(state);
			if ((bs->states[0]).blockt != BlockType::None && 
				(bs->states[0]).blockt != BlockType::Hint) {
				if ((bs->states[0]).r >= 0) {
					currClear();
					clearcurr = false;
				} else {
					nextClear();
				}
			}
			for (int i = 0; i < (bs->states).size(); i++) {
				int index_r = (bs->states[i]).r;
				int index_c = (bs->states[i]).c;
				BlockType bt = (bs->states[i]).blockt;
				if (bt == BlockType::Hint || bt == BlockType::None) {
					textDis[index_r][index_c] = transform_char(bt);
				} else if (index_r >= 0){
					textDis[index_r][index_c] = transform_char(bt);
					curr.emplace_back(pair<int, int>(index_r, index_c));
				} else {
					index_r = (- index_r) - 1;
					next[index_r][index_c] = transform_char(bt);
				}
			}
		}
	}
}


std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	out << "Level:    " << td.level << endl;
	out << "Score:    " << td.score << endl;
	out << "Hi Score: " << td.hiscore << endl;
    out << "-----------" << endl;
    for (int i = 0; i < td.height; i++) {
    	for (int j = 0; j < td.width; j++) {
    		out << td.textDis[i][j];
    	}
    	out << endl;
    }
    out << "-----------" << endl;
    out << "Next:" << endl;
    for (int i = 0; i < td.next_h; i++) {
    	for (int j = 0; j < td.next_w; j++) {
    		out << td.next[i][j];
    	}
    	out << endl;
    }
    return out;
}
