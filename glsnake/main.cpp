#include "app.hpp"
#include "scene.hpp"
#include "xml-parser.hpp"
#include "xml-tree.hpp"
#include "xml-node.hpp"

#include <glm/glm.hpp>
#include <iostream>

int main() {
	//App::Instance().RegisterScene(Scene::SNAKE, InitSnake, DeinitSnake);
	//if (App::Instance().Init() == -1) {
	//	return -1;
	//}

	App::Instance().RegisterScene(Scene::SNAKE, InitSnake, DeinitSnake);
	App::Instance().Init();
	App::Instance().Loop();
	App::Instance().Deinit();

	return 0;
}