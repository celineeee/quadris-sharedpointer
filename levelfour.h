#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include "level.h"

class LevelFour : public Level{
	const int levelNum = 4;
public:
	int getLevelNum() const override;
	LevelFour(int seed, bool useSeed);
	void accept(LevelVisitor *lv, Block **preturn) override;
	void accept(LevelVisitor *lv, Block *block, Block **preturn) override;
};


#endif

