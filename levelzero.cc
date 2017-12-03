#include "levelzero.h"
#include "levelvisitor.h"

LevelZero::LevelZero(int seed, bool useSeed): Level{seed, useSeed}{}

int LevelZero::getLevelNum() const{
	return levelNum;
}

void LevelZero::accept(LevelVisitor *lv, Block **preturn) {
	return;
}

void LevelZero::accept(LevelVisitor *lv, Block *block, Block **preturn){
	return;
}

