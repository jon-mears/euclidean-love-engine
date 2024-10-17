#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "gameobject.h"
#include "shader.h"
#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

enum : char {
	COLOR,
	TEXTURE
};

class SpriteRenderer : public Renderer {
private:
	void static_init();

	union {
		glm::vec4 color;
		GLuint texture;
	};
	char type;
	
	static Shader* s;
	static bool static_inited;
	static GLuint VAO;
	
public:
	SpriteRenderer(GameObject* go);
	void set_color(float r, float g, float b, float a);
	~SpriteRenderer() = default;
};
#endif