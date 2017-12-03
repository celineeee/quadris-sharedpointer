#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "level.h"

class LevelTwo: public Level{
	const int levelNum = 2;
public:
	int getLevelNum() const override;
	LevelTwo(int seed, bool useSeed);
	void accept(shared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn) override;
	void accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn) override;
};


#endif


