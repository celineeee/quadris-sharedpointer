#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include "level.h"

class LevelFour : public Level{
	const int levelNum = 4;
public:
	int getLevelNum() const override;
	LevelFour(int seed, bool useSeed);
	void accept(shared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn) override;
	void accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn) override;
};


#endif

