#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <map>
#include <string>
#include <array>

class Shader {
private:
	GLuint program;
	std::map<std::string, GLuint> uniforms;

public:
	Shader(const char* vertexShaderSource, const char* fragmentShaderSource);

	void set_uniform(const std::string& uniform_name, float f1);
	void set_uniform(const std::string& uniform_name, float f1, float f2);
	void set_uniform(const std::string& uniform_name, float f1, float f2, float f3);
	void set_uniform(const std::string& uniform_name, float f1, float f2, float f3, float f4);
};

#endif