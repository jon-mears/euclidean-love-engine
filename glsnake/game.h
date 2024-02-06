#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "gameobject.h"
#include "grid.h"

class Game {
private:
	enum class Cells : int {
		EMPTY_CELL,
		SNAKE_CELL,
		FOOD_CELL,
		WALL_CELL
	};

	int glInit();
	int userInit();

	void process_input();
	void update();
	void draw();

	GLFWwindow* window;
	std::vector<GameObject*> objects;
	
public:
	int init();
	void loop();
	void deinit();
};

#endif