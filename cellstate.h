#ifndef CELLSTATE_H
#define CELLSTATE_H
#include "blocktype.h"
#include "state.h"

struct CellState: public State {
	int r;
	int c;
	BlockType blockt;
	CellState(int r, int c, BlockType blockt);
};

#endif
