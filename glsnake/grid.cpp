#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "grid.h"

GLuint Grid::VAO = 0;
GLuint Grid::program = 0;
GLint Grid::uColor = 0;
GLint Grid::uModel = 0;
bool Grid::is_initialized = false;

void Grid::draw() const {
	GLint prevVAO, prevProgram;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prevVAO);
	glGetIntegerv(GL_CURRENT_PROGRAM, &prevProgram);
	
	glBindVertexArray(VAO);
	glUseProgram(program);

	// could also cache the model matrix...

	float startX, startY, x, y, deltaX, deltaY;

	float originX = ((cell_scale.x * c + (c - 1) * spacing.x) / 2.0f);
	float originY = -((cell_scale.y * r + (r - 1) * spacing.y) / 2.0f);

	// could cache the positions...

	startX = pos.x - originX;
	startX += 0.5 * cell_scale.x;
	x = startX;
	deltaX = cell_scale.x + spacing.x;

	startY = pos.y - originY;
	startY -= 0.5 * cell_scale.y;
	y = startY;
	deltaY = cell_scale.y + spacing.y;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {

			glm::vec4 color = p.get(grid[i][j]);
			glUniform4f(uColor, color.r, color.g, color.b, color.a);

			glm::mat4 model = glm::mat4(1.0f);

			model = glm::translate(model, glm::vec3(x, y, 0.0f));
			model = glm::scale(model, glm::vec3(cell_scale.x, cell_scale.y, 1.0f));

			glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
			x += deltaX;

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		x = startX;
		y -= deltaY;
	}
}

void Grid::set_total_rect(float x, float y, float width, float height, spacing_scale choice) {
	pos.x = x + width / 2.0f;
	pos.y = y - height / 2.0f;

	if (choice == SPACING) {
		float tempX = (width - c * cell_scale.x) / (float)(c - 1);
		float tempY = (height - r * cell_scale.y) / (float)(r - 1);

		if (tempX < 0 || tempY < 0) return;

		spacing.x = tempX;
		spacing.y = tempY;
	}

	else {  // choice == SCALE
		cell_scale.x = (width - (c - 1) * spacing.x) / (float)c;
		cell_scale.y = (height - (r - 1) * spacing.y) / (float)r;
	}
}

void Grid::init() {
	int success;
	char infoLog[512];

	// square
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // bottom-left
		-0.5f, 0.5f, 0.0f,  // top-left
		0.5f, 0.5f, 0.0f,   // top-right
		0.5f, -0.5f, 0.0f  // bottom-right
	};

	GLuint indices[] = {
		0, 1, 3, // left-triangle
		3, 2, 1  // right-triangle 
	};

	GLint prevVBO, prevEBO, prevVAO, prevProgram;
	GLuint VBO, EBO;

	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prevVBO);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &prevEBO);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prevVAO);
	glGetIntegerv(GL_CURRENT_PROGRAM, &prevProgram);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, prevVBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prevEBO);
	glBindVertexArray(prevVAO);

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 uModel;\n"
		"void main() {\n"
		"	gl_Position = uModel * vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"}";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 uColor;\n"
		"void main() {\n"
		"	FragColor = uColor;\n"
		"}";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION::GRID_VERTEX_SHADER\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION::GRID_FRAGMENT_SHADER\n" << infoLog << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING::GRID_SHADER_PROGRAM\n" << infoLog << std::endl;
	}

	glUseProgram(program);
	uColor = glGetUniformLocation(program, "uColor");
	uModel = glGetUniformLocation(program, "uModel");

	glUseProgram(prevProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	is_initialized = true;
}

Grid::Grid(const std::vector<std::vector<int>> &grid) : spacing(0.0f, 0.0f), pos(glm::vec2(0.0f, 0.0f)), cell_scale(glm::vec2(1.0f, 1.0f)),
grid(grid), p(), r(grid.size()), c(grid[0].size()) {
	if (!is_initialized) init();
}

Grid::Grid(int rows, int cols) : spacing(0.0f, 0.0f), pos(glm::vec2(0.0f, 0.0f)), cell_scale(glm::vec2(1.0f, 1.0f)), 
grid(rows, std::vector<int>(cols, 0)), p(), r(rows), c(cols) {
	if (!is_initialized) init();
}

Grid::Grid() : spacing(0.0f), pos(glm::vec2(0.0f, 0.0f)), cell_scale(glm::vec2(1.0f, 1.0f)),
grid(5, std::vector<int>(5, 0)), p(), r(5), c(5) {
	if (!is_initialized) init();
}