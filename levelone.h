#ifndef LEVELONE_H
#define LEVELONE_H

#include "level.h"

class LevelOne: public Level{
	const int levelNum = 1;
public:
	LevelOne(int seed, bool useSeed);
	int getLevelNum() const override;
	void accept(LevelVisitor *lv, Block **preturn) override;
	void accept(LevelVisitor *lv, Block *block, Block **preturn) override;
};


#endif



