#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "observer.h"
#include "window.h"
#include <vector>
#undef None

class GraphicsDisplay: public Observer{
	int board_width;
	int board_height;
	int cellsize;
	int linesize;
	int linenum;
	int win_width;
	int win_height;
	Xwindow xw;
	int level;
	int score;
	int hiscore;
	int board_start;
	int next_start;
	bool clearcurr;
	std::vector<std::pair<int, int>> curr;
	void nextClear();
	void currClear();
public:
	GraphicsDisplay(int board_width, int board_height, int level, int score, int hiscore);
	void notify(Subject &whoNotified) override;
};

#endif
