#ifndef LEVELONE_H
#define LEVELONE_H

#include "level.h"

class LevelOne: public Level{
	const int levelNum = 1;
public:
	LevelOne(int seed, bool useSeed);
	int getLevelNum() const override;
	void accept(std::shared_ptr<LevelVisitor> lv, std::shared_ptr<std::shared_ptr<Block>> preturn) override;
	void accept(std::shared_ptr<LevelVisitor> lv, 
		std::shared_ptr<Block> block, std::shared_ptr<std::shared_ptr<Block>> preturn) override;
};


#endif



