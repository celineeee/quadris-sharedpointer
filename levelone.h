#ifndef LEVELONE_H
#define LEVELONE_H

#include "level.h"

class LevelOne: public Level{
	const int levelNum = 1;
public:
	LevelOne(int seed, bool useSeed);
	int getLevelNum() const override;
	void accept(shared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn) override;
	void accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn) override;
};


#endif



