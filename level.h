#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "block.h"

class LevelVisitor;


class Level{
	int seed;
	bool useSeed = false;
protected:
	Level(int seed, bool useSeed);

public:
	int getSeed() const;
	bool hasSeed() const;
	virtual int getLevelNum() const = 0;
	virtual void accept(std::shared_ptr<LevelVisitor> lv, 
		std::shared_ptr<std::shared_ptr<Block>> preturn) = 0;
	virtual void accept(std::shared_ptr<LevelVisitor> lv, 
		std::shared_ptr<Block> block, 
		std::shared_ptr<std::shared_ptr<Block>> preturn) = 0;
	virtual ~Level() = default;
};


#endif

