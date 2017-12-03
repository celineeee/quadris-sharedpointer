#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "state.h"

struct GameState: public State {
	int level;
	int score;
	int hiscore;
	GameState(int level, int score, int hiscore);
};

#endif
