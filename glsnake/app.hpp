#ifndef APP_HPP
#define APP_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>
#include <string>
	
enum class Scene;
class Resources;
class Shader;
class Model; 
class GameObject;
class App;
class CameraComponent;
class ResourceManager;
class UIWindow;

typedef void (*SceneFunc)(App*);
typedef void (*UniformUpdater)(GameObject*, CameraComponent*);


class App {
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

	void Update();

	std::map<Scene, SceneFunc> mInitScenes;
	std::map<Scene, SceneFunc> mDeinitScenes;

	//std::map<std::string, Window*> mWindows;
	//Window* mWindow;

	GLFWwindow* mpWindow;

	App();

	bool ShouldClose();
	
public:
	void RegisterScene(Scene scene, SceneFunc init, SceneFunc deinit);

	int Init();
	void StartSystems();
	void Loop();
	void Deinit();

	GLFWwindow* Window();
	static App& Instance();
};
#endif