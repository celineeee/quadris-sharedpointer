#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "block.h"

class LevelVisitor;
using namespace std;

class Level{
	int seed;
	bool useSeed = false;
protected:
	Level(int seed, bool useSeed);

public:
	int getSeed() const;
	bool hasSeed() const;
	virtual int getLevelNum() const = 0;
	virtual void accept(LevelVisitor *lv, Block **preturn) = 0;
	virtual void accept(LevelVisitor *lv, 
		Block *block, Block **preturn) = 0;
	virtual ~Level() = default;
};


#endif

