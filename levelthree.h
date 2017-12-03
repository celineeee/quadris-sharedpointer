#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "level.h"

class LevelThree: public Level{
	const int levelNum = 3;
public:
	int getLevelNum() const override;
	LevelThree(int seed, bool useSeed);
	void accept(std::shared_ptr<LevelVisitor> lv, std::shared_ptr<std::shared_ptr<Block>> preturn) override;
	void accept(std::shared_ptr<LevelVisitor> lv, 
		std::shared_ptr<Block> block, std::shared_ptr<std::shared_ptr<Block>> preturn) override;
};


#endif

