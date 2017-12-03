#ifndef LEVELZERO_H
#define LEVELZERO_H



#include "level.h"

class LevelZero : public Level{
	const int levelNum = 0;
	LevelZero();
public:
	int getLevelNum() const override;
	LevelZero(int seed, bool useSeed);
	void accept(std::shared_ptr<LevelVisitor> lv, std::shared_ptr<std::shared_ptr<Block>> preturn) override;
	void accept(std::shared_ptr<LevelVisitor> lv, 
		std::shared_ptr<Block> block, std::shared_ptr<std::shared_ptr<Block>> preturn) override;

};

#endif

