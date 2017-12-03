#ifndef HEAVY_H
#define HEAVY_H

#include "levelvisitor.h"

class Heavy : public LevelVisitor{
public:

	shared_ptr<Block> visit(LevelZero &lzero) override;
	shared_ptr<Block> visit(LevelZero &lzero, shared_ptr<Block> block) override;
	shared_ptr<Block> visit(LevelOne &lone) override;
	shared_ptr<Block> visit(LevelOne &lone, shared_ptr<Block> block) override;
	shared_ptr<Block> visit(LevelTwo &ltwo) override;
	shared_ptr<Block> visit(LevelTwo &ltwo, shared_ptr<Block> block) override;
	shared_ptr<Block> visit(LevelThree &lthree) override;
	shared_ptr<Block> visit(LevelThree &lthree, shared_ptr<Block> block) override;
	shared_ptr<Block> visit(LevelFour &lfour) override;
	shared_ptr<Block> visit(LevelFour &lfour, shared_ptr<Block> block) override;

};


#endif



