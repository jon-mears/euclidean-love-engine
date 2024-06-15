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

typedef void (*StateFunc)(Game*);
typedef void (*UniformUpdater)(GameObject*, Camera*);

class Game {
private:

	/**
	 * \brief	Complete setup related to the graphics library.
	 * \details	Creates the window, sets the OpenGL version, and sets the framebuffer resize callback.
	 * \author	Jon Mears
	 */
	int glInit();

	///**
	// * \brief
	// * 
	// */
	//int userInit();

	void process_input();
	void update();
	void draw();

	GLFWwindow* _window;
	int width, height;
	std::string title;
	std::map<State, StateFunc> init_states;
	std::map<State, StateFunc> deinit_states;

	std::map<std::string, Shader*> shaders;
	std::map<std::string, Model*> models;
	std::map<std::string, GameObject*> gameobjects;
	
public:
	Game(std::string t = "", int w = 600, int h = 600);

	void register_state(State s, StateFunc init, StateFunc deinit);

	int init();
	void loop();
	void deinit();

	Shader* add_shader(std::string name);
	Model* add_model(std::string name);
	GameObject* add_gameobject(std::string name);
	Shader* shader(const std::string& name);
	Model* model(const std::string& name);
	GameObject* gameobject(const std::string& name);

	GLFWwindow* window();
};
#endif