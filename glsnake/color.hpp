#ifndef COLOR_HPP
#define COLOR_HPP

#include <glm/glm.hpp>

class Color {
private:
	
public:
	glm::vec4 value;

	static const Color WHITE;
	static const Color BLACK;

	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;

	Color(float r, float g, float b, float a = 1.0f);
	Color(glm::vec3 color);
	Color(glm::vec4 color);
};
#endif