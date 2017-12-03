#include "generator.h"
#include "level.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
using namespace std;
bool Generator::takenSeed = false;

shared_ptr<Block> Generator::visit(LevelZero &lzero){
	return nullptr;
}


shared_ptr<Block> Generator::visit(LevelZero &lzero, shared_ptr<Block> block){
	return nullptr;
}

shared_ptr<Block> Generator::visit(LevelOne &lone){
	shared_ptr<Block> block;
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
		case 0: block = make_shared<Block>(BlockType::I, lone.getLevelNum());
				break;
		case 1: block = make_shared<Block>(BlockType::I, lone.getLevelNum());
				break;
		case 2: block = make_shared<Block>(BlockType::J, lone.getLevelNum());
				break;
		case 3: block = make_shared<Block>(BlockType::J, lone.getLevelNum());
				break;
		case 4: block = make_shared<Block>(BlockType::L, lone.getLevelNum());
				break;
		case 5: block = make_shared<Block>(BlockType::L, lone.getLevelNum());
				break;
		case 6: block = make_shared<Block>(BlockType::O, lone.getLevelNum());
				break;
		case 7: block = make_shared<Block>(BlockType::O, lone.getLevelNum());
				break;
		case 8: block = make_shared<Block>(BlockType::T, lone.getLevelNum());
				break;
		case 9: block = make_shared<Block>(BlockType::T, lone.getLevelNum());
				break;
		case 10: block = make_shared<Block>(BlockType::S, lone.getLevelNum());
				break;
		case 11: block = make_shared<Block>(BlockType::Z, lone.getLevelNum());
				break;

	}
	return block;
}

shared_ptr<Block> Generator::visit(LevelOne &lone, shared_ptr<Block> block{
	return nullptr;
}

shared_ptr<Block> Generator::visit(LevelTwo &ltwo){
	shared_ptr<Block> block;
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
		case 0: block = make_shared<Block>(BlockType::I, ltwo.getLevelNum());
				break;
		case 1: block = make_shared<Block>(BlockType::J, ltwo.getLevelNum());
				break;
		case 2: block = make_shared<Block>(BlockType::L, ltwo.getLevelNum());
				break;
		case 3: block = make_shared<Block>(BlockType::O, ltwo.getLevelNum());
				break;
		case 4: block = make_shared<Block>(BlockType::S, ltwo.getLevelNum());
				break;
		case 5: block = make_shared<Block>(BlockType::Z, ltwo.getLevelNum());
				break;
		case 6: block = make_shared<Block>(BlockType::T, ltwo.getLevelNum());
				break;
		
	}
	return block;
}

shared_ptr<Block> Generator::visit(LevelTwo &ltwo, shared_ptr<Block> block){
	return nullptr;
}

shared_ptr<Block> Generator::visit(LevelThree &lthree){
    shared_ptr<Block> block;
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
		case 0: block = make_shared<Block>(BlockType::I, lthree.getLevelNum());
				break;
		case 1: block = make_shared<Block>(BlockType::J, lthree.getLevelNum());
				break;
		case 2: block = make_shared<Block>(BlockType::L, lthree.getLevelNum());
				break;
		case 3: block = make_shared<Block>(BlockType::O, lthree.getLevelNum());
				break;
		case 4: block = make_shared<Block>(BlockType::S, lthree.getLevelNum());
				break;
		case 5: block = make_shared<Block>(BlockType::Z, lthree.getLevelNum());
				break;
		case 6: block = make_shared<Block>(BlockType::T, lthree.getLevelNum());
				break;
		case 7: block = make_shared<Block>(BlockType::S, lthree.getLevelNum());
				break;
		case 8: block = make_shared<Block>(BlockType::Z, lthree.getLevelNum());
				break;
		
	}
	return block;
}

shared_ptr<Block> Generator::visit(LevelThree &lthree, shared_ptr<Block> block){
	return nullptr;
}

shared_ptr<Block> Generator::visit(LevelFour &lfour){
	shared_ptr<Block> block;
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
		case 0: block = make_shared<Block>(BlockType::I, lfour.getLevelNum());
				break;
		case 1: block = make_shared<Block>(BlockType::J, lfour.getLevelNum());
				break;
		case 2: block = make_shared<Block>(BlockType::L, lfour.getLevelNum());
				break;
		case 3: block = make_shared<Block>(BlockType::O, lfour.getLevelNum());
				break;
		case 4: block = make_shared<Block>(BlockType::S, lfour.getLevelNum());
				break;
		case 5: block = make_shared<Block>(BlockType::Z, lfour.getLevelNum());
				break;
		case 6: block = make_shared<Block>(BlockType::T, lfour.getLevelNum());
				break;
		case 7: block = make_shared<Block>(BlockType::S, lfour.getLevelNum());
				break;
		case 8: block = make_shared<Block>(BlockType::Z, lfour.getLevelNum());
				break;
		
	}
	return block;
}

shared_ptr<Block> Generator::visit(LevelFour &lfour, shared_ptr<Block> block){
	return nullptr;
}


