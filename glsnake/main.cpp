#include "game.h"
#include "states.h"

int main() {
	Game* g = new Game("glSnake", 600, 600);
	g->register_state(State::SNAKE, init_snake, deinit_snake);

	if (g->init() == -1) {
		delete g;
		return -1;
	}

	g->loop();
	g->deinit();

	delete g;

	return 0;
}