#include "levelvisitor.h"
#include "levelfour.h"

using namespace std;
LevelFour::LevelFour(int seed, bool useSeed):Level{seed, useSeed}{}

int LevelFour::getLevelNum() const{
	return levelNum;
}

void LevelFour::accept(shared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn){
	*preturn = lv->visit(*this);
}

void LevelFour::accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn){
	*preturn = lv->visit(*this, block);
}

