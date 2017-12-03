#include "levelvisitor.h"
#include "leveltwo.h"

using namespace std;
LevelTwo::LevelTwo(int seed, bool useSeed):Level{seed, useSeed}{}
int LevelTwo::getLevelNum() const{
	return levelNum;
}

void LevelTwo::accept(shared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn){
	*preturn = lv->visit(*this);
}

void LevelTwo::accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn){
	*preturn = lv->visit(*this, block);
}

