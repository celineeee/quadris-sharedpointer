#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "level.h"

class LevelTwo: public Level{
	const int levelNum = 2;
public:
	int getLevelNum() const override;
	LevelTwo(int seed, bool useSeed);
	void accept(std::shared_ptr<LevelVisitor> lv, std::shared_ptr<std::shared_ptr<Block>> preturn) override;
	void accept(std::shared_ptr<LevelVisitor> lv, 
		std::shared_ptr<Block> block, std::shared_ptr<std::shared_ptr<Block>> preturn) override;
};


#endif


