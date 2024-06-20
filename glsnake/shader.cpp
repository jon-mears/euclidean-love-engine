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

#include "model.h"
#include "glsltranslator.hpp"

void Shader::enable() {
	glUseProgram(program);
}

void Shader::disable() {
	glUseProgram(0);
}

void Shader::vertex(std::string &source) {
	char infoLog[512];
	GLint success;

	GLSL_Translator::translate(source);
	vsource = source.c_str();

	vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vsource, NULL);
	glCompileShader(vshader);

	glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vshader, 512, NULL, infoLog);
		std::cout << "ERROR COMPILING VERTEX SHADER\n" << infoLog << std::endl;
		std::exit(-1);
	}
}

void Shader::fragment(std::string &source) {

	char infoLog[512];
	GLint success;

	GLSL_Translator::translate(source);

	fsource = source.c_str();

	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fsource, NULL);
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

	std::cout << fsource << std::endl;

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

			//_uniforms[var] = Factories::make_uniform(var, loc, type);
			mUniformCodes.push_back(Uniform::encode(var, loc, type));
		}

		if (word == "in") {
			vertexStream >> type;
			vertexStream >> var;
			var = var.substr(0, var.size() - 1); // get rid of semicolon at end
			GLuint loc = glGetAttribLocation(program, var.c_str());

			mAttribName2Loc[var] = loc;
			mAttribName2Type[var] = Attribute::NONE;
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

			//_uniforms[var] = Factories::make_uniform(var, loc, type);
			mUniformCodes.push_back(Uniform::encode(var, loc, type));
		}
	}
}

std::vector<std::string> &Shader::uniform_codes() {
	return mUniformCodes;
}

std::string &Shader::name() {
	return mName;
}

void Shader::name(const std::string &name) {
	mName = name;
}

void Shader::label_attrib(const std::string& name, Attribute attrib) {
	mAttribName2Type[name] = attrib;
}