#include "levelvisitor.h"
#include "leveltwo.h"


LevelTwo::LevelTwo(int seed, bool useSeed):Level{seed, useSeed}{}
int LevelTwo::getLevelNum() const{
	return levelNum;
}

void LevelTwo::accept(LevelVisitor *lv, Block **preturn){
	*preturn = lv->visit(*this);
}

void LevelTwo::accept(LevelVisitor *lv, Block *block, Block **preturn){
	*preturn = lv->visit(*this, block);
}

