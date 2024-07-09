#ifndef GLSL_TRANSLATOR_HPP
#define GLSL_TRANSLATOR_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex-data.hpp"
#include "mesh.hpp"

namespace GLSLTranslator {
	GLuint Attrib2Loc(Vertex::Attribute eAttrib);
	std::string Translate(std::string source);
}
#endif