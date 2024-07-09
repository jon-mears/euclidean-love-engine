#ifndef SCENE_HPP
#define SCENE_HPP

class App;
class CameraComponent;
class GameObject;

typedef void (*SceneFunc)(App*);
typedef void (*UniformUpdater)(GameObject*, CameraComponent*);

/* name the game states (0-valued state is the initial state) */
enum class Scene : int {
	SNAKE = 0
};

extern const Scene InitScene;
	
void UniformUpdater(GameObject* pGO, CameraComponent* pCamera);
void InitSnake(App* pApp);
void DeinitSnake(App* pApp);
#endif