#ifndef STATES_H
#define STATES_H

#include "game.h"

typedef void (*StateFunc)(Game*);

/* name the game states (0-valued state is the initial state) */
enum class State : int {
	SNAKE = 0
};

extern const State Init_State = static_cast<State>(0);

/* define init funcs per game state */
void init_snake(Game *g) {
	
}

void deinit_snake(Game *g) {
	
}

void empty(Game *g) { return; }
#endif