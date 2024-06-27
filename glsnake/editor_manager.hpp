#ifndef EDITOR_MANAGER_HPP
#define EDITOR_MANAGER_HPP

class GameObject;
class UIWindow;

#include <vector>

class EditorManager {
private:

	std::vector<UIWindow*> mEditors;

	void startup();
	void draw();

	EditorManager();

	EditorManager(EditorManager& lhs) = delete;
	EditorManager& operator=(EditorManager& lhs) = delete;
	EditorManager& operator=(EditorManager lhs) = delete;

public:
	GameObject* mpSelected;

	static EditorManager& instance();
	friend class Game;
};
#endif