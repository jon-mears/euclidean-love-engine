#ifndef PALETTE_H
#define PALETTE_H
#include <vector> 

#include <glm/glm.hpp>

class Palette {
private:
	std::vector<glm::vec4> colors;
public:
	Palette(std::vector<glm::vec4> colors) : colors(colors) { }

	// creates a simple default palette
	Palette() : colors{ glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) } { }

	void add(glm::vec4 color) {
		colors.push_back(color);
	}

	void add(glm::vec3 color) {
		colors.push_back(glm::vec4(color, 1.0f));
	}

	void update(const std::vector<glm::vec4> &colors) {
		this->colors = colors;
	}

	glm::vec4 get(int idx) const {
		return colors[idx];
	}
};
#endif