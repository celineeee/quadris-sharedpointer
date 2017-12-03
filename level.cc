#include "level.h"
#include "levelvisitor.h"

Level::Level(int seed, bool useSeed):seed{seed}, useSeed{useSeed}{}



int Level::getSeed()const{
	return seed;
}

bool Level::hasSeed()const{
	return useSeed;
}

