#ifndef LEVELZERO_H
#define LEVELZERO_H



#include "level.h"

class LevelZero : public Level{
	const int levelNum = 0;
	LevelZero();
public:
	int getLevelNum() const override;
	LevelZero(int seed, bool useSeed);
	void accept(Lshared_ptr<LevelVisitor> lv, shared_ptr<shared_ptr<Block>> preturn) override;
	void accept(shared_ptr<LevelVisitor> lv, 
		shared_ptr<Block> block, shared_ptr<shared_ptr<Block>> preturn) override;

};

#endif

