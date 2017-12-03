#include "levelvisitor.h"
#include "levelone.h"
#include <iostream>


LevelOne::LevelOne(int seed, bool useSeed):Level{seed, useSeed}{}

int LevelOne::getLevelNum() const{
	return levelNum;
}

void LevelOne::accept(LevelVisitor *lv, Block **preturn){
    *preturn = lv->visit(*this);
}

void LevelOne::accept(LevelVisitor *lv, Block *block, Block **preturn){
	*preturn = lv->visit(*this, block);
}

