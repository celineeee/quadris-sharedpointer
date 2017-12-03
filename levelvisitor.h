#ifndef LEVELVISITOR_H
#define LEVELVISITOR_H

#include "blocktype.h"
#include "block.h"

class Level;
class LevelZero;
class LevelOne;
class LevelTwo;
class LevelThree;
class LevelFour;




class LevelVisitor{
public:

	virtual std::shared_ptr<Block> visit(LevelZero &lzero) = 0;
	virtual std::shared_ptr<Block> visit(LevelZero &lzero, std::shared_ptr<Block> block) = 0;
	virtual std::shared_ptr<Block> visit(LevelOne &lone) = 0;
	virtual std::shared_ptr<Block> visit(LevelOne &lone, std::shared_ptr<Block> block) = 0;
	virtual std::shared_ptr<Block> visit(LevelTwo &ltwo) = 0;
	virtual std::shared_ptr<Block> visit(LevelTwo &ltwo, std::shared_ptr<Block> block) = 0;
	virtual std::shared_ptr<Block> visit(LevelThree &lthree) = 0;
	virtual std::shared_ptr<Block> visit(LevelThree &lthree, std::shared_ptr<Block> block) = 0;
	virtual std::shared_ptr<Block> visit(LevelFour &lfour) = 0;
	virtual std::shared_ptr<Block> visit(LevelFour &lfuor, std::shared_ptr<Block> block) = 0;

	virtual ~LevelVisitor() = default;

};

#endif


