#ifndef GRIDCOMPONENT_H
#define GRIDCOMPONENT_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "palette.h"

class GridComponent : public Component {
private:
	void init();

	glm::vec2 spacing;
	glm::vec2 pos;
	glm::vec2 cell_scale;
	std::vector<std::vector<int>> grid;
	Palette p;
	int _rows;
	int _cols;

	static GLuint VAO;
	static GLuint program;
	static GLint uColor;
	static GLint uModel;
	static bool is_initialized;

public:

	enum spacing_scale {
		SPACING,
		SCALE
	};

	// ctors
	GridComponent(const std::vector<std::vector<int>> &grid);
	GridComponent(int rows, int cols);
	GridComponent();

	void set(int row, int col, int val) {
		grid[row][col] = val;
	}

	int get(int row, int col) {
		return grid[row][col];
	}

	void set_spacing(glm::vec2 new_spacing) {
		spacing = new_spacing;
	}

	void set_pos(float x, float y) {
		pos.x = x;
		pos.y = y;
	}

	void set_scale(float x, float y) {
		cell_scale.x = x;
		cell_scale.y = y;
	}

	void set_total_rect(float x, float y, float width, float height, spacing_scale choice);

	int rows() const {
		return _rows;
	}

	int cols() const {
		return _cols;
	}

	void draw() const;
};

#endif