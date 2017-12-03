#include "generator.h"
#include "level.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
bool Generator::takenSeed = false;

Block *Generator::visit(LevelZero &lzero){
	return nullptr;
}


Block *Generator::visit(LevelZero &lzero, Block *block){
	return nullptr;
}

Block *Generator::visit(LevelOne &lone){
	Block *block;
	int curr;
	if(lone.hasSeed() && !Generator::takenSeed){
        srand(lone.getSeed());
		curr = rand() % 12;
		Generator::takenSeed = true;
	}
	else{
		curr = rand() % 12;
	}
	switch(curr){
		case 0: block = new Block(BlockType::I, lone.getLevelNum());
				break;
		case 1: block = new Block(BlockType::I, lone.getLevelNum());
				break;
		case 2: block = new Block(BlockType::J, lone.getLevelNum());
				break;
		case 3: block = new Block(BlockType::J, lone.getLevelNum());
				break;
		case 4: block = new Block(BlockType::L, lone.getLevelNum());
				break;
		case 5: block = new Block(BlockType::L, lone.getLevelNum());
				break;
		case 6: block = new Block(BlockType::O, lone.getLevelNum());
				break;
		case 7: block = new Block(BlockType::O, lone.getLevelNum());
				break;
		case 8: block = new Block(BlockType::T, lone.getLevelNum());
				break;
		case 9: block = new Block(BlockType::T, lone.getLevelNum());
				break;
		case 10: block = new Block(BlockType::S, lone.getLevelNum());
				break;
		case 11: block = new Block(BlockType::Z, lone.getLevelNum());
				break;

	}
	return block;
}

Block *Generator::visit(LevelOne &lone, Block *block){
	return nullptr;
}

Block *Generator::visit(LevelTwo &ltwo){
	Block *block;
	int curr;
	if(ltwo.hasSeed() && !Generator::takenSeed){
        srand(ltwo.getSeed());
        curr = rand() % 7;
        Generator::takenSeed = true;
	}
	else{
		curr = rand() % 7;
	}
	switch(curr){
		case 0: block = new Block(BlockType::I, ltwo.getLevelNum());
				break;
		case 1: block = new Block(BlockType::J, ltwo.getLevelNum());
				break;
		case 2: block = new Block(BlockType::L, ltwo.getLevelNum());
				break;
		case 3: block = new Block(BlockType::O, ltwo.getLevelNum());
				break;
		case 4: block = new Block(BlockType::S, ltwo.getLevelNum());
				break;
		case 5: block = new Block(BlockType::Z, ltwo.getLevelNum());
				break;
		case 6: block = new Block(BlockType::T, ltwo.getLevelNum());
				break;
		
	}
	return block;
}

Block *Generator::visit(LevelTwo &ltwo, Block *block){
	return nullptr;
}

Block *Generator::visit(LevelThree &lthree){
    Block *block;
	int curr;
	if(lthree.hasSeed() && !Generator::takenSeed){
        srand(lthree.getSeed());
        curr = rand() % 9;
        Generator::takenSeed = true;
	}
	else{
		curr = rand() % 9;
	}
	switch(curr){
		case 0: block = new Block(BlockType::I, lthree.getLevelNum());
				break;
		case 1: block = new Block(BlockType::J, lthree.getLevelNum());
				break;
		case 2: block = new Block(BlockType::L, lthree.getLevelNum());
				break;
		case 3: block = new Block(BlockType::O, lthree.getLevelNum());
				break;
		case 4: block = new Block(BlockType::S, lthree.getLevelNum());
				break;
		case 5: block = new Block(BlockType::Z, lthree.getLevelNum());
				break;
		case 6: block = new Block(BlockType::T, lthree.getLevelNum());
				break;
		case 7: block = new Block(BlockType::S, lthree.getLevelNum());
				break;
		case 8: block = new Block(BlockType::Z, lthree.getLevelNum());
				break;
		
	}
	return block;
}

Block *Generator::visit(LevelThree &lthree, Block *block){
	return nullptr;
}

Block *Generator::visit(LevelFour &lfour){
	Block *block;
	int curr;
	if(lfour.hasSeed() && !Generator::takenSeed){
        srand(lfour.getSeed());
        curr = rand() % 9;
        Generator::takenSeed = true;
	}
	else{
		curr = rand() % 9;
	}
	switch(curr){
		case 0: block = new Block(BlockType::I, lfour.getLevelNum());
				break;
		case 1: block = new Block(BlockType::J, lfour.getLevelNum());
				break;
		case 2: block = new Block(BlockType::L, lfour.getLevelNum());
				break;
		case 3: block = new Block(BlockType::O, lfour.getLevelNum());
				break;
		case 4: block = new Block(BlockType::S, lfour.getLevelNum());
				break;
		case 5: block = new Block(BlockType::Z, lfour.getLevelNum());
				break;
		case 6: block = new Block(BlockType::T, lfour.getLevelNum());
				break;
		case 7: block = new Block(BlockType::S, lfour.getLevelNum());
				break;
		case 8: block = new Block(BlockType::Z, lfour.getLevelNum());
				break;
		
	}
	return block;
}

Block *Generator::visit(LevelFour &lfour, Block *block){
	return nullptr;
}


