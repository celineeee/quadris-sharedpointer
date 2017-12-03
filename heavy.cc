#include "heavy.h"

Block *Heavy::visit(LevelZero &lzero){
	return nullptr;
}

Block * Heavy::visit(LevelZero &lzero, Block *block){
	return nullptr;
}

Block *Heavy::visit(LevelOne &lone){
	return nullptr;
}

Block *Heavy::visit(LevelOne &lone, Block *block){
	return nullptr;
}

Block *Heavy::visit(LevelTwo &ltwo){
	return nullptr;
}

Block *Heavy::visit(LevelTwo &ltwo, Block *block){
	return nullptr;
}

Block *Heavy::visit(LevelThree &lthree){
	return nullptr;
}

Block *Heavy::visit(LevelThree &lthree, Block *block){
	Block *copy = block->down();
	return copy;
}

Block *Heavy::visit(LevelFour &lfour){
	return nullptr;
}

Block *Heavy::visit(LevelFour &lfour, Block *block){
	Block *copy = block->down();
	return copy;
}

