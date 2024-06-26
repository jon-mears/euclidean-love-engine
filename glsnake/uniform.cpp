#include "uniform.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture2d.hpp"

Uniform::Uniform(const std::string &name, GLuint loc) : name(name), loc(loc) { }

// static
std::string Uniform::encode(std::string name, GLuint loc, std::string type) {
	return name + ":" + std::to_string(loc) + ":" + type;
}

// static
Uniform* Uniform::decode(const std::string& code) {
	size_t colon_pos1 = code.find(":");
	size_t colon_pos2 = code.find(":", colon_pos1 + 1);

	if (colon_pos1 == std::string::npos) {
		std::cout << "uniform codes must contain a colon!" << std::endl;
		std::exit(-1);
	}

	if (colon_pos2 == std::string::npos) {
		std::cout << "uniform codes must contain two colons!" << std::endl;
		std::exit(-1);
	}

	std::string name = code.substr(0, colon_pos1);
	std::string loc = code.substr(colon_pos1 + 1, colon_pos2 - colon_pos1 - 1);
	std::string type = code.substr(colon_pos2 + 1);

	if (type == "vec3") {
		return new Uniform3f(name, std::atoi(loc.c_str()));
	}

	else if (type == "vec4") {
		return new Uniform4f(name, std::atoi(loc.c_str()));
	}

	else if (type == "mat4") {
		return new UniformMat4(name, std::atoi(loc.c_str()));
	}

	else if (type == "sampler2D") {
		return new UniformTexture2D(name, std::atoi(loc.c_str()));
	}

	else {
		std::cout << "this has not yet been implemented." << std::endl;
		std::exit(-1);
	}
}

void Uniform::set(float v0) {
	throw "ERROR :: CANNOT SET " + name + " TO FLOAT";
}

void Uniform::set(float v0, float v1) {
	throw "ERROR :: CANNOT SET " + name + " TO FLOAT2";
}

void Uniform::set(const glm::vec2 &v) {
	throw "ERROR :: CANNOT SET " + name + " TO FLOAT2";
}

void Uniform::set(float v0, float v1, float v2) {
	throw "ERROR :: CANNOT SET " + name + " TO FLOAT3";
}

void Uniform::set(const glm::vec3 &v) {
	throw "ERROR :: CANNOT SET " + name + " TO FLOAT3";
}

void Uniform::set(float v0, float v1, float v2, float v3) {
	throw "ERROR :: CANNOT SET " + name + " TO FLOAT4";
}

void Uniform::set(const glm::vec4 &v) {
	throw "ERROR :: CANNOT SET " + name + " TO FLOAT4";
}

void Uniform::set(int v0) {
	throw "ERROR :: CANNOT SET " + name + " TO INT";
}

void Uniform::set(int v0, int v1) {
	throw "ERROR :: CANNOT SET " + name + " TO INT2";
}

void Uniform::set(const glm::ivec2 &v) {
	throw "ERROR :: CANNOT SET " + name + " TO INT2";
}

void Uniform::set(int v0, int v1, int v2) {
	throw "ERROR :: CANNOT SET " + name + " TO INT3";
}

void Uniform::set(const glm::ivec3 &v) {
	throw "ERROR :: CANNOT SET " + name + " TO INT3";
}

void Uniform::set(int v0, int v1, int v2, int v3) {
	throw "ERROR :: CANNOT SET " + name + " TO INT4";
}

void Uniform::set(const glm::ivec4 &v) {
	throw "ERROR :: CANNOT SET " + name + " TO INT4";
}

void Uniform::set(const glm::mat2 &m) {
	throw "ERROR :: CANNOT SET " + name + " TO MAT2";
}

void Uniform::set(const glm::mat3 &m) {
	throw "ERROR :: CANNOT SET " + name + " TO MAT3";
}

void Uniform::set(const glm::mat4 &m) {
	std::cout << "can't set uniform " << name << " to matrix4!" << std::endl;
	exit(-1);
}

void Uniform::set(Texture2D* tex) {
	std::cout << "can't set uniform " << name << " to texture2D!" << std::endl;
	std::exit(-1);
}

Uniform1f::Uniform1f(const std::string &name, GLuint loc) : Uniform(name, loc), v0(0) { }

void Uniform1f::set(float v0) {
	this->v0 = v0;
}

void Uniform1f::upload() {
	glUniform1f(loc, v0);
}

Uniform2f::Uniform2f(const std::string &name, GLuint loc) : Uniform(name, loc), v() { }

void Uniform2f::set(float v0, float v1) {
	v = { v0, v1 };
}

void Uniform2f::set(const glm::vec2 &v) {
	this->v = v;
}

void Uniform2f::upload() {
	glUniform2fv(loc, 1, glm::value_ptr(v));
}

Uniform3f::Uniform3f(const std::string &name, GLuint loc) : Uniform(name, loc), v() { }

void Uniform3f::set(float v0, float v1, float v2) {
	v = { v0, v1, v2 };
}

void Uniform3f::set(const glm::vec3 &v) {
	this->v = v;
}

void Uniform3f::upload() {
	glUniform3fv(loc, 1, glm::value_ptr(v));
}

Uniform4f::Uniform4f(const std::string &name, GLuint loc) : Uniform(name, loc), v() { }

void Uniform4f::set(float v0, float v1, float v2, float v3) {
	v = { v0, v1, v2, v3 };
}

void Uniform4f::set(const glm::vec4 &v) {
	this->v = v;
}

void Uniform4f::upload() {
	glUniform4fv(loc, 1, glm::value_ptr(v));
}

Uniform1i::Uniform1i(const std::string &name, GLuint loc) : Uniform(name, loc), v0(0) { }

void Uniform1i::set(int v0) {
	this->v0 = v0;
}

void Uniform1i::upload() {
	glUniform1i(loc, v0);
}

Uniform2i::Uniform2i(const std::string &name, GLuint loc) : Uniform(name, loc), v() { }

void Uniform2i::set(int v0, int v1) {
	v = { v0, v1 };
}

void Uniform2i::set(const glm::ivec2 &v) {
	this->v = v;
}

void Uniform2i::upload() {
	glUniform2iv(loc, 1, glm::value_ptr(v));
}

Uniform3i::Uniform3i(const std::string &name, GLuint loc) : Uniform(name, loc), v() { }

void Uniform3i::set(int v0, int v1, int v2) {
	v = { v0, v1, v2 };
}

void Uniform3i::set(const glm::ivec3 &v) {
	this->v = v;
}

void Uniform3i::upload() {
	glUniform3iv(loc, 1, glm::value_ptr(v));
}

Uniform4i::Uniform4i(const std::string &name, GLuint loc) : Uniform(name, loc), v() { }

void Uniform4i::set(int v0, int v1, int v2, int v3) {
	v = { v0, v1, v2, v3 };
}

void Uniform4i::set(const glm::ivec4 &v) {
	this->v = v;
}

void Uniform4i::upload() {
	glUniform4iv(loc, 1, glm::value_ptr(v));
}

UniformMat2::UniformMat2(const std::string &name, GLuint loc) : Uniform(name, loc), m() { }

void UniformMat2::set(const glm::mat2& matrix) {
	m = matrix;
}

void UniformMat2::upload() {
	glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

UniformMat3::UniformMat3(const std::string &name, GLuint loc) : Uniform(name, loc), m() { }

void UniformMat3::set(const glm::mat3& matrix) {
	m = matrix;
}

void UniformMat3::upload() {
	glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

UniformMat4::UniformMat4(const std::string &name, GLuint loc) : Uniform(name, loc), m() { }

void UniformMat4::set(const glm::mat4& matrix) {
	m = matrix;
}

void UniformMat4::upload() {
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

UniformTexture2D::UniformTexture2D(const std::string& name, GLuint loc) : Uniform(name, loc), t() { }

void UniformTexture2D::set(Texture2D* tex) {
	t = tex;
}

void UniformTexture2D::upload() {
	t->enable();
}