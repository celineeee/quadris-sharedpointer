#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "level.h"

class LevelTwo: public Level{
	const int levelNum = 2;
public:
	int getLevelNum() const override;
	LevelTwo(int seed, bool useSeed);
	void accept(LevelVisitor *lv, Block **preturn) override;
	void accept(LevelVisitor *lv, Block *block, Block **preturn) override;
};


#endif


