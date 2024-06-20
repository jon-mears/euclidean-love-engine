#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class Attribute;

namespace GLSL_Translator {
	GLuint attrib2loc(Attribute attrib);
	void translate(std::string& source);
}