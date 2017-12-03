#include "levelvisitor.h"
#include "levelthree.h"


LevelThree::LevelThree(int seed, bool useSeed):Level{seed, useSeed}{}

int LevelThree::getLevelNum() const{
	return levelNum;
}

void LevelThree::accept(shared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn){
	*preturn = lv->visit(*this);
}

void LevelThree::accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn){
	*preturn = lv->visit(*this, block);
}

