#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>
#include <string>

#include "gameobject.h"
#include "states.h"
#include "grid.h"

class Game {
private:
	int glInit();
	int userInit();

	void process_input();
	void update();
	void draw();

	GLFWwindow* window;
	int width, height;
	std::string title;
	std::vector<GameObject*> objects;
	std::map<State, StateFunc> init_states;
	std::map<State, StateFunc> deinit_states;
	
public:
	Game(std::string t = "", int w = 600, int h = 600) : window(nullptr), width(w), height(h), title(t), objects() { }

	void register_state(State s, StateFunc init, StateFunc deinit = empty) {
		init_states[s] = init;
		deinit_states[s] = deinit;
	}

	int init();
	void start();
	void deinit();
};

#endif