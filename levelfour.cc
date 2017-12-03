#include "levelvisitor.h"
#include "levelfour.h"


LevelFour::LevelFour(int seed, bool useSeed):Level{seed, useSeed}{}

int LevelFour::getLevelNum() const{
	return levelNum;
}

void LevelFour::accept(LevelVisitor *lv, Block **preturn){
	*preturn = lv->visit(*this);
}

void LevelFour::accept(LevelVisitor *lv, Block *block, Block **preturn){
	*preturn = lv->visit(*this, block);
}

