#ifndef LEVELZERO_H
#define LEVELZERO_H



#include "level.h"

class LevelZero : public Level{
	const int levelNum = 0;
	LevelZero();
public:
	int getLevelNum() const override;
	LevelZero(int seed, bool useSeed);
	void accept(LevelVisitor *lv, Block **preturn) override;
	void accept(LevelVisitor *lv, Block *block, Block **preturn) override;

};

#endif

