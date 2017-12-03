#include <iostream>
#include "graphicsdisplay.h"
#include "cellstate.h"
#include "blockstate.h"
#include "gamestate.h"
#include "subject.h"
#undef None
using namespace std;

GraphicsDisplay::GraphicsDisplay(int board_width, int board_height, int level, int score, int hiscore):
 board_width{board_width}, board_height{board_height}, cellsize{30}, linesize{30}, linenum{4}, 
 win_width{board_width*cellsize}, win_height{(board_height+2)*cellsize+linenum*linesize}, 
 xw{win_width, win_height}, level{level}, score{score}, hiscore{hiscore}, 
 board_start{(linenum-1)*linesize}, next_start{win_height-cellsize*2} {
 	xw.fillRectangle(0, 0, win_width, win_height, Xwindow::White);
 	xw.drawString(10, 10+0*linesize, "Level:");
 	xw.drawString(100, 10, to_string(level));
 	xw.drawString(10, 10+1*linesize, "Score:");
 	xw.drawString(100, 10+1*linesize, to_string(score));
 	xw.drawString(10, 10+2*linesize, "Hi score:");
 	xw.drawString(100, 10+2*linesize, to_string(hiscore));
 	xw.drawString(0, 20+2*linesize, "---------------------------------------");
 	xw.drawString(0, board_start+board_height*cellsize+10, "---------------------------------------");
 	xw.drawString(10, board_start+board_height*cellsize+20, "Next:");
 }


void GraphicsDisplay::nextClear() {
	xw.fillRectangle(0, next_start, win_width, 2*cellsize, Xwindow::White);
}

void GraphicsDisplay::currClear() {
	for (int i = 0; i < curr.size(); i++) {
		int index_r = curr[i].first;
		int index_c = curr[i].second;
		xw.fillRectangle(index_c*cellsize, board_start+index_r*cellsize, cellsize, 
			cellsize, Xwindow::White);
	}
	curr.clear();
	clearcurr = true;
}

void GraphicsDisplay::notify(Subject &whoNotified) {
	State *state = whoNotified.getState();
	GameState *gs = dynamic_cast<GameState *>(state);
	if (gs) {
		level = gs->level;
		hiscore = gs->hiscore;
		score = gs->score;
		xw.fillRectangle(100,0*linesize,win_width-100,10,0);
		xw.drawString(100, 10, to_string(level));
		xw.fillRectangle(100,1*linesize,win_width-100,10,0);
		xw.drawString(100, 10+1*linesize, to_string(score));
		xw.fillRectangle(100,2*linesize,win_width-100,10,0);
		xw.drawString(100, 10+2*linesize, to_string(hiscore));
	} else {
		CellState *cs = dynamic_cast<CellState *>(state);
		if (cs) {
			if (!clearcurr) {
				currClear();
				clearcurr = true;
			}
			int index_r = cs->r;
			int index_c = cs->c;
			BlockType bt = cs->blockt;
			xw.fillRectangle(index_c*cellsize, board_start+index_r*cellsize, cellsize, 
				cellsize, transform_colour(bt));
		} else {
			BlockState *bs = dynamic_cast<BlockState *>(state);
			if ((bs->states[0]).blockt != BlockType::None && 
				(bs->states[0]).blockt != BlockType::Hint) {
				if ((bs->states[0]).r >= 0) {
					currClear();
				} else {
					nextClear();
				}
			}
			for (int i = 0; i < (bs->states).size(); i++) {
				int index_r = (bs->states[i]).r;
				int index_c = (bs->states[i]).c;
				BlockType bt = (bs->states[i]).blockt;
				if (bt == BlockType::Hint || bt == BlockType::None) {
					xw.fillRectangle(index_c*cellsize, board_start+index_r*cellsize, cellsize, 
						cellsize, transform_colour(bt));
				} else if (index_r >= 0){
					xw.fillRectangle(index_c*cellsize, board_start+index_r*cellsize, cellsize, 
						cellsize, transform_colour(bt));
					curr.emplace_back(pair<int, int>(index_r, index_c));
					clearcurr = false;
				} else {
					index_r = (- index_r) - 1;
					xw.fillRectangle(index_c*cellsize, next_start+index_r*cellsize, cellsize, 
						cellsize, transform_colour(bt));
				}
			}
		}
	}
}
