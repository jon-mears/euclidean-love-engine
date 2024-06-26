#include "game.h"
#include "states.h"
#include "window.hpp"
#include "xmlparser.hpp"
#include "xmltree.hpp"
#include "xmlnode.hpp"

#include <glm/glm.hpp>
#include <iostream>

int main() {
	Game::instance()->add_window(new Window("Pong", 600, 600, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}));
	Game::instance()->register_state(State::SNAKE, init_snake, deinit_snake);

	if (Game::instance()->init() == -1) {
		return -1;
	}

	Game::instance()->loop();
	Game::instance()->deinit();

	return 0;
}