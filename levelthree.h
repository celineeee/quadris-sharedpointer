#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "level.h"

class LevelThree: public Level{
	const int levelNum = 3;
public:
	int getLevelNum() const override;
	LevelThree(int seed, bool useSeed);
	void accept(shared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn) override;
	void accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn) override;
};


#endif

