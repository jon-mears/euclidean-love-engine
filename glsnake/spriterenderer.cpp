#include "spriterenderer.h"
#include "gameobject.h"
#include "component.h"

#include <glm/glm.hpp>

void SpriteRenderer::static_init() {
	static_inited = true;

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		"out vec2 vTexCoord;\n"
		"void main() {\n"
		"	vTexCoord = aTexCoord;\n"
		"	gl_Position = vec4(aPos, 1.0);\n"
		"}";

	const char* fragmentShaderSource = "#version 330 core\n"
		"uniform vec3 uColor;\n"
		"out vec4 gl_FragColor;\n"
		"void main() {\n"
		"	gl_FragColor = vec4(uColor, 1.0f);\n"
		"}";

	s = new Shader(vertexShaderSource, fragmentShaderSource);

	GLfloat vertices[] = {
		// 3D position ... 2D tex coordinate

		// FIRST TRIANGLE 
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom-left
		-0.5f, 0.5f, 0.0f,   0.0f, 1.0f,   // top-left
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f,   // top-right

		 // SECOND TRIANGLE
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom-right
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f,   // top-right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f    // bottom-left
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

SpriteRenderer::SpriteRenderer(GameObject* go) : Renderer(go), color({ 1.0f, 1.0f, 1.0f, 1.0f}),
type{ static_cast<char>(COLOR) } {
	if (!static_inited) static_init();
	drawer->register_object(this);
}

void SpriteRenderer::set_color(float r, float g, float b, float a) {
	color = glm::vec4(r, g, b, a);
}