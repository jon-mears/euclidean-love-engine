#include "glsl-translator.hpp"
#include "mesh.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define VERSION "#version 330 core"

namespace GLSLTranslator {

	GLuint Attrib2Loc(Vertex::Attribute eAttrib) {
		switch (eAttrib) {
		case Vertex::POSITION:
			return 0;
		case Vertex::Attribute::VERTEX_COLOR:
			return 1;
		case Vertex::Attribute::TEXTURE_COORD:
			return 2;
		default:
			return -1;
		}
	}

	std::string Translate(std::string source) {
		size_t version = source.find("@VERSION");

		if (version != std::string::npos) {
			source.replace(version, 8, VERSION);
		}

		size_t position = source.find("@POSITION");

		if (position != std::string::npos)
			source.replace(position, 9, "layout (location=" + std::to_string(Attrib2Loc(Vertex::Attribute::POSITION)) + ")");

		position = source.find("@VERTEX_COLOR");

		if (position != std::string::npos)
			source.replace(position, 13, "layout (location=1)");

		position = source.find("@TEXTURE_COORD");

		if (position != std::string::npos)
			source.replace(position, 14, "layout (location=2)");

		return source;
	}
}