#include "glsltranslator.hpp"
#include "model.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GLSL_Translator {

	GLuint attrib2loc(Attribute attrib) {
		switch (attrib) {
		case Attribute::POSITION:
			return 0;
		case Attribute::VERTEX_COLOR:
			return 1;
		default:
			return -1;
		}
	}

	void translate(std::string& source) {
		size_t position = source.find("@POSITION");

		if (position != std::string::npos)
			source.replace(position, 9, "layout (location=" + std::to_string(attrib2loc(Attribute::POSITION)) + ")");

		position = source.find("@VERTEX_COLOR");

		if (position != std::string::npos)
			source.replace(position, 13, "layout (location=1)");
	}
}