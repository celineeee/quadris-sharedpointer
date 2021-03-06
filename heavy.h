#ifndef HEAVY_H
#define HEAVY_H

#include "levelvisitor.h"

class Heavy : public LevelVisitor{
public:

	std::shared_ptr<Block> visit(LevelZero &lzero) override;
	std::shared_ptr<Block> visit(LevelZero &lzero, std::shared_ptr<Block> block) override;
	std::shared_ptr<Block> visit(LevelOne &lone) override;
	std::shared_ptr<Block> visit(LevelOne &lone, std::shared_ptr<Block> block) override;
	std::shared_ptr<Block> visit(LevelTwo &ltwo) override;
	std::shared_ptr<Block> visit(LevelTwo &ltwo, std::shared_ptr<Block> block) override;
	std::shared_ptr<Block> visit(LevelThree &lthree) override;
	std::shared_ptr<Block> visit(LevelThree &lthree, std::shared_ptr<Block> block) override;
	std::shared_ptr<Block> visit(LevelFour &lfour) override;
	std::shared_ptr<Block> visit(LevelFour &lfour, std::shared_ptr<Block> block) override;

};


#endif



