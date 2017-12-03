#include "levelvisitor.h"
#include "levelthree.h"


LevelThree::LevelThree(int seed, bool useSeed):Level{seed, useSeed}{}

int LevelThree::getLevelNum() const{
	return levelNum;
}

void LevelThree::accept(LevelVisitor *lv, Block **preturn){
	*preturn = lv->visit(*this);
}

void LevelThree::accept(LevelVisitor *lv, Block *block, Block **preturn){
	*preturn = lv->visit(*this, block);
}

