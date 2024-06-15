#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <map>
#include <string>
#include <glm/glm.hpp>

class Uniform;

class Shader {
private:
	GLuint program;
	GLuint vshader = -1;
	GLuint fshader = -1;

	const char* vsource;
	const char* fsource;

	std::map<std::string, Uniform*> _uniforms;

public:
	void vertex(const char* source);
	void fragment(const char* source);
	void enable();
	void disable();
	//void set_uniform(const std::string& name, const glm::mat4& value);
	void compile();
	std::map<std::string, Uniform*> uniforms();
};

#endif