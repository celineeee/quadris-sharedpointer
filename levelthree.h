#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "level.h"

class LevelThree: public Level{
	const int levelNum = 3;
public:
	int getLevelNum() const override;
	LevelThree(int seed, bool useSeed);
	void accept(LevelVisitor *lv, Block **preturn) override;
	void accept(LevelVisitor *lv, Block *block, Block **preturn) override;
};


#endif

