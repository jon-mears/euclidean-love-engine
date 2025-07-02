#include "color.hpp"

#include <glm/glm.hpp>

Color::Color(float r, float g, float b, float a) : value{ r, g, b,a } { }

Color::Color(glm::vec3 color) : value{ color.r, color.g, color.b, 1.0f } { }

Color::Color(glm::vec4 color) : value{ color } { } 

const Color Color::WHITE{ 1.0f, 1.0f, 1.0f, 1.0f };
const Color Color::BLACK{ 0.0f, 0.0f, 0.0f, 1.0f };

const Color Color::RED{ 1.0f, 0.0f, 0.0f, 1.0f };
const Color Color::GREEN{ 0.0f, 1.0f, 0.0f, 1.0f };
const Color Color::BLUE{ 0.0f, 0.0f, 1.0f, 1.0f };
