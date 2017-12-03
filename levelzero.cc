#include "levelzero.h"
#include "levelvisitor.h"

LevelZero::LevelZero(int seed, bool useSeed): Level{seed, useSeed}{}

int LevelZero::getLevelNum() const{
	return levelNum;
}

void LevelZero::accept(shared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn) {
	return;
}

void LevelZero::accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn){
	return;
}

