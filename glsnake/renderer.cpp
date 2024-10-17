#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Renderer::draw() {
	glUseProgram(program);
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}