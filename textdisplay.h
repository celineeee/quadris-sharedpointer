#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"

class TextDisplay: public Observer {
	std::vector<std::pair<int, int>> curr;
	std::vector<std::vector<char>> textDis;
	std::vector<std::vector<char>> next;
	int next_w;
	int next_h;
	int width;
	int height;
	int level;
	int score;
	int hiscore;
	bool clearcurr;
	void nextClear();
	void currClear();

public:
	TextDisplay(int width, int height, int level, int score, int hiscore);
	void notify(Subject &whoNotified) override;
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
