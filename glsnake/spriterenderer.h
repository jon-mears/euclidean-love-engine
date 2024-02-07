#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "component.h"
#include "gameobject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

enum {
	TEXTURE,
	COLOR
};

class SpriteRenderer : public Component {
private:
	glm::vec3 color;

	static GLuint program;
	static bool static_inited;

public:
	SpriteRenderer(GameObject* go) : Component(go), color({1.0f, 1.0f, 1.0f}) {
		
	}

	~SpriteRenderer() = default;
};
#endif