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

	virtual Block *visit(LevelZero &lzero) = 0;
	virtual Block *visit(LevelZero &lzero, Block *block) = 0;
	virtual Block *visit(LevelOne &lone) = 0;
	virtual Block *visit(LevelOne &lone, Block *block) = 0;
	virtual Block *visit(LevelTwo &ltwo) = 0;
	virtual Block *visit(LevelTwo &ltwo, Block *block) = 0;
	virtual Block *visit(LevelThree &lthree) = 0;
	virtual Block *visit(LevelThree &lthree, Block *block) = 0;
	virtual Block *visit(LevelFour &lfour) = 0;
	virtual Block *visit(LevelFour &lfuor, Block *block) = 0;

	virtual ~LevelVisitor() = default;

};

#endif


