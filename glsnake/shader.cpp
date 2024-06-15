#include "shader.h"

#include <iostream>
#include <sstream>
#include <ios>
#include <string>
#include <utility>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "factories.h"
#include "uniform.h"

void Shader::enable() {
	glUseProgram(program);
}

void Shader::disable() {
	glUseProgram(0);
}

void Shader::vertex(const char* source) {
	char infoLog[512];
	GLint success;

	vsource = source;

	vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &source, NULL);
	glCompileShader(vshader);

	glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vshader, 512, NULL, infoLog);
		std::cout << "ERROR COMPILING VERTEX SHADER\n" << infoLog << std::endl;
		std::exit(-1);
	}
}

void Shader::fragment(const char* source) {
	char infoLog[512];
	GLint success;

	fsource = source;

	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &source, NULL);
	glCompileShader(fshader);

	glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fshader, 512, NULL, infoLog);
		std::cout << "ERROR COMPILING FRAGMENT SHADER\n" << infoLog << std::endl;
		std::exit(-1);
	}
}

void Shader::compile() {
	char infoLog[512];
	GLint success;

	this->program = glCreateProgram();

	glAttachShader(this->program, vshader);
	glAttachShader(this->program, fshader);

	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cout << "ERROR LINKING PROGRAM\n" << infoLog << std::endl;
		std::exit(-1);
	}	

	std::string word, type, var;

	std::istringstream vertexStream(vsource);
	while (vertexStream && word != "main") {
		vertexStream >> word;

		if (word == "uniform") {
			vertexStream >> type;
			vertexStream >> var;
			var = var.substr(0, var.size() - 1); // get rid of semicolon at end
			GLuint loc = glGetUniformLocation(this->program, var.c_str());

			_uniforms[var] = Factories::make_uniform(var, loc, type);
		}
	}

	std::istringstream fragmentStream(fsource);
	while (fragmentStream && word != "main") {
		fragmentStream >> word;

		if (word == "uniform") {
			fragmentStream >> type;
			fragmentStream >> var;
			var = var.substr(0, var.size() - 1); // get rid of semicolon at end
			GLuint loc = glGetUniformLocation(this->program, var.c_str());

			_uniforms[var] = Factories::make_uniform(var, loc, type);
		}
	}
}

std::map<std::string, Uniform*> Shader::uniforms() {
	return _uniforms;
}

//void Shader::set_uniform(const std::string& s, const glm::mat4& mat) {
//	
//	//for (std::pair<const std::string, Uniform*>& it : uniforms) {
//	//	std::cout << "uniform: " << it.first << std::endl;
//
//	//	if ()
//	//}
//	
//	if (!uniforms.count(s)) {
//		std::cout << "error :: attempt to access non-existent uniform " << s << std::endl;
//		exit(-1);
//	}
//
//	uniforms[s]->set(mat);
//
//	enable();
//	uniforms[s]->upload();
//	disable();
//}