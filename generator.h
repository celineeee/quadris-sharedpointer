#ifndef GENERATOR_H
#define GENERATOR_H

#include "levelvisitor.h"
#include <cstdlib>

class Generator : public LevelVisitor{
	static bool takenSeed; 
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



