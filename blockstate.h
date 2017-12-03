#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H
#include "state.h"
#include <vector>

struct CellState;
struct BlockState: public State {
	std::vector<CellState> states;
	BlockState(std::vector<CellState> states);
};

#endif
