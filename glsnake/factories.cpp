#include "factories.h"
#include "uniform.h"

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Factories {
	Uniform* make_uniform(std::string name, GLuint loc, std::string type) {
		if (type == "float") {
			return new Uniform1f(name, loc);
		}
		else if (type == "vec2") {
			return new Uniform2f(name, loc);
		}
		else if (type == "vec3") {
			return new Uniform3f(name, loc);
		}
		else if (type == "vec4") {
			return new Uniform4f(name, loc);
		}
		else if (type == "int") {
			return new Uniform1i(name, loc);
		}
		else if (type == "ivec2") {
			return new Uniform2i(name, loc);
		}
		else if (type == "ivec3") {
			return new Uniform3i(name, loc);
		}
		else if (type == "ivec4") {
			return new Uniform4i(name, loc);
		}
		else if (type == "mat2") {
			return new UniformMat2(name, loc);
		}
		else if (type == "mat3") {
			return new UniformMat3(name, loc);
		}
		else if (type == "mat4") {
			return new UniformMat4(name, loc);
		}

		return nullptr;
	}
}