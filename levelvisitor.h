#ifndef LEVELVISITOR_H
#define LEVELVISITOR_H

#include "blocktype.h"
#include "block.h"

using namespace std;
class Level;
class LevelZero;
class LevelOne;
class LevelTwo;
class LevelThree;
class LevelFour;




class LevelVisitor{
public:

	virtual shared_ptr<Block> visit(LevelZero &lzero) = 0;
	virtual shared_ptr<Block> visit(LevelZero &lzero, shared_ptr<Block> block) = 0;
	virtual shared_ptr<Block> visit(LevelOne &lone) = 0;
	virtual shared_ptr<Block> visit(LevelOne &lone, shared_ptr<Block> block) = 0;
	virtual shared_ptr<Block> visit(LevelTwo &ltwo) = 0;
	virtual shared_ptr<Block> visit(LevelTwo &ltwo, shared_ptr<Block> block) = 0;
	virtual shared_ptr<Block> visit(LevelThree &lthree) = 0;
	virtual shared_ptr<Block> visit(LevelThree &lthree, shared_ptr<Block> block) = 0;
	virtual shared_ptr<Block> visit(LevelFour &lfour) = 0;
	virtual shared_ptr<Block> visit(LevelFour &lfuor, shared_ptr<Block> block) = 0;

	virtual ~LevelVisitor() = default;

};

#endif


