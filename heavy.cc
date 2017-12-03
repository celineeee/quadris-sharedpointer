#include "heavy.h"

shared_ptr<Block> Heavy::visit(LevelZero &lzero){
	return nullptr;
}

shared_ptr<Block> Heavy::visit(LevelZero &lzero, shared_ptr<Block> block){
	return nullptr;
}

shared_ptr<Block> Heavy::visit(LevelOne &lone){
	return nullptr;
}

shared_ptr<Block> Heavy::visit(LevelOne &lone, shared_ptr<Block> block){
	return nullptr;
}

shared_ptr<Block> Heavy::visit(LevelTwo &ltwo){
	return nullptr;
}

shared_ptr<Block> Heavy::visit(LevelTwo &ltwo, shared_ptr<Block> block){
	return nullptr;
}

shared_ptr<Block> Heavy::visit(LevelThree &lthree){
	return nullptr;
}

shared_ptr<Block> Heavy::visit(LevelThree &lthree, shared_ptr<Block> block){
	shared_ptr<Block> copy = block->down();
	return copy;
}

shared_ptr<Block> Heavy::visit(LevelFour &lfour){
	return nullptr;
}

shared_ptr<Block> Heavy::visit(LevelFour &lfour, shared_ptr<Block> block){
	shared_ptr<Block> copy = block->down();
	return copy;
}

