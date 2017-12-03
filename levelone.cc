#include "levelvisitor.h"
#include "levelone.h"
#include <iostream>
using namespace std;

LevelOne::LevelOne(int seed, bool useSeed):Level{seed, useSeed}{}

int LevelOne::getLevelNum() const{
	return levelNum;
}

void LevelOne::accept(shared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn){
    *preturn = lv->visit(*this);
}

void LevelOne::accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn){
	*preturn = lv->visit(*this, block);
}

