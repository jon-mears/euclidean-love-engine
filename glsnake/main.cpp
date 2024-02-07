#include "game.h"

int main() {
	Game* g = new Game("glSnake", 600, 600);

	if (g->init() == -1) {
		delete g;
		return -1;
	}

	g->register_state(State::SNAKE, init_snake, deinit_snake);
	g->start();
	g->deinit();

	delete g;

	return 0;
}