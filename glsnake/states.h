#ifndef STATES_H
#define STATES_H

class Game;
class Camera;
class GameObject;

typedef void (*StateFunc)(Game*);
typedef void (*UniformUpdater)(GameObject*, Camera*);

/* name the game states (0-valued state is the initial state) */
enum class State : int {
	SNAKE = 0
};

extern const State Init_State;
	
void uniform_updater(GameObject* go, Camera* c);
void init_snake(Game* g);
void deinit_snake(Game* g);

#endif