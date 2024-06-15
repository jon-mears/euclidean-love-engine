#ifndef FACTORIES_H
#define FACTORIES_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Uniform;

namespace Factories {
	Uniform* make_uniform(std::string name, GLuint loc, std::string type);
}
#endif