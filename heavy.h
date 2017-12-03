#ifndef HEAVY_H
#define HEAVY_H

#include "levelvisitor.h"

class Heavy : public LevelVisitor{
public:

	Block *visit(LevelZero &lzero) override;
	Block *visit(LevelZero &lzero, Block *block) override;
	Block *visit(LevelOne &lone) override;
	Block *visit(LevelOne &lone, Block *block) override;
	Block *visit(LevelTwo &ltwo) override;
	Block *visit(LevelTwo &ltwo, Block *block) override;
	Block *visit(LevelThree &lthree) override;
	Block *visit(LevelThree &lthree, Block *block) override;
	Block *visit(LevelFour &lfour) override;
	Block *visit(LevelFour &lfour, Block *block) override;

};


#endif



