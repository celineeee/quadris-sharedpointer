#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include "level.h"

class LevelFour : public Level{
	const int levelNum = 4;
public:
	int getLevelNum() const override;
	LevelFour(int seed, bool useSeed);
	void accept(std::shared_ptr<LevelVisitor> lv, std::shared_ptr<std::shared_ptr<Block>> preturn) override;
	void accept(std::shared_ptr<LevelVisitor> lv, 
		std::shared_ptr<Block> block, std::shared_ptr<std::shared_ptr<Block>> preturn) override;
};


#endif

