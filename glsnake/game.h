#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>
#include <string>
	
enum class State;
class Resources;
class Shader;
class Model; 
class GameObject;
class Game;
class Camera;
class ResourceManager;
class UIWindow;

typedef void (*StateFunc)(Game*);
typedef void (*UniformUpdater)(GameObject*, Camera*);


class Game {
private:
	/**
	 * \brief	Complete setup related to the graphics library.
	 * \details	Creates the window, sets the OpenGL version, and sets the framebuffer resize callback.
	 * \author	Jon Mears
	 */

	///**
	// * \brief
	// * 
	// */
	//int userInit();

	void update();
	void draw();

	std::map<State, StateFunc> init_states;
	std::map<State, StateFunc> deinit_states;

	//std::map<std::string, Window*> mWindows;
	//Window* mWindow;

	GLFWwindow* mpWindow;

	Game();

	bool should_close();
	void swap_buffers();
	inline void poll_events();

	void imgui_start();
	void imgui_end();
	
public:
	void register_state(State s, StateFunc init, StateFunc deinit);

	int init();
	void start_systems();
	void loop();
	void deinit();

	GLFWwindow* window();
	static Game& instance();
};
#endif