#include "shader.h"

#include <iostream>
#include <sstream>
#include <ios>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Shader::set_uniform(const std::string &uniform_name, float f1) {
	glUniform1f(uniforms[uniform_name], f1);
}

void Shader::set_uniform(const std::string& uniform_name, float f1, float f2) {
	glUniform2f(uniforms[uniform_name], f1, f2);
}

void Shader::set_uniform(const std::string& uniform_name, float f1, float f2, float f3) {
	glUniform3f(uniforms[uniform_name], f1, f2, f3);
}

void Shader::set_uniform(const std::string& uniform_name, float f1, float f2, float f3, float f4) {
	glUniform4f(uniforms[uniform_name], f1, f2, f3, f4);
}

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource) : program(0) {
	char infoLog[512];
	GLint success;
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR COMPILING VERTEX SHADER\n" << infoLog << std::endl;
		std::exit(-1);
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR COMPILING FRAGMENT SHADER\n" << infoLog << std::endl;
		std::exit(-1);
	}

	this->program = glCreateProgram();

	glAttachShader(this->program, vertexShader);
	glAttachShader(this->program, fragmentShader);

	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cout << "ERROR LINKING PROGRAM\n" << infoLog << std::endl;
		std::exit(-1);
	}	

	glUseProgram(this->program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	std::istringstream vertexStream(vertexShaderSource);
	std::string word;

	while (vertexStream && word != "main") {
		vertexStream >> word;
		
		if (word == "uniform") {
			vertexStream >> word; // ignore the type
			vertexStream >> word;
			uniforms[word] = glGetUniformLocation(this->program, word.c_str());
		}
	}

	std::istringstream fragmentStream(fragmentShaderSource);

	while (fragmentStream && word != "main") {
		fragmentStream >> word;

		if (word == "uniform") {
			fragmentStream >> word; // ignore the type
			fragmentStream >> word;
			uniforms[word] = glGetUniformLocation(this->program, word.c_str());
		}
	}
}