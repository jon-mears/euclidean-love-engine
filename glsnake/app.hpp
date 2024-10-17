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

class RootWindow;

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

	SceneFunc mInitScene;
	SceneFunc mDeinitScene;

	//std::map<std::string, Window*> mWindows;
	//Window* mWindow;

	GLFWwindow* mpWindow;
	RootWindow* mpRootWindow;

	App();
	 
	bool ShouldClose();
	
public:
	int Init();
	void StartSystems();
	void StartRootWindow();
	void Loop();
	void Deinit();

	void RegisterScene(Scene eScene, SceneFunc init, SceneFunc deinit);

	GLFWwindow* Window();
	static App& Instance();
};
#endif