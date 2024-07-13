#include "uniform.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.hpp"

Uniform::Uniform(const std::string& name, GLuint loc) : mName{ name }, mLoc{ loc } { }

// static
std::string Uniform::Encode(std::string name, GLuint loc, std::string type) {
	return name + ":" + std::to_string(loc) + ":" + type;
}

// static
Uniform* Uniform::Decode(const std::string& code) {
	size_t colon_pos1 = code.find(":");
	size_t colon_pos2 = code.find(":", colon_pos1 + 1);
	size_t colon_pos3 = code.find(":", colon_pos2 + 1);

	bool bIsSpecial = colon_pos3 != std::string::npos;

	if (colon_pos1 == std::string::npos) {
		std::cerr << "uniform codes must contain a colon!" << std::endl;
		std::exit(-1);
	}

	if (colon_pos2 == std::string::npos) {
		std::cerr << "uniform codes must contain two colons!" << std::endl;
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

void Uniform::Set(float v0) {
	throw "ERROR :: CANNOT SET " + mName + " TO FLOAT";
}

void Uniform::Set(float v0, float v1) {
	throw "ERROR :: CANNOT SET " + mName + " TO FLOAT2";
}

void Uniform::Set(const glm::vec2 &v) {
	throw "ERROR :: CANNOT SET " + mName + " TO FLOAT2";
}

void Uniform::Set(float v0, float v1, float v2) {
	throw "ERROR :: CANNOT SET " + mName + " TO FLOAT3";
}

void Uniform::Set(const glm::vec3 &v) {
	throw "ERROR :: CANNOT SET " + mName + " TO FLOAT3";
}

void Uniform::Set(float v0, float v1, float v2, float v3) {
	throw "ERROR :: CANNOT SET " + mName + " TO FLOAT4";
}

void Uniform::Set(const glm::vec4 &v) {
	throw "ERROR :: CANNOT SET " + mName + " TO FLOAT4";
}

void Uniform::Set(int v0) {
	throw "ERROR :: CANNOT SET " + mName + " TO INT";
}

void Uniform::Set(int v0, int v1) {
	throw "ERROR :: CANNOT SET " + mName + " TO INT2";
}

void Uniform::Set(const glm::ivec2 &v) {
	throw "ERROR :: CANNOT SET " + mName + " TO INT2";
}

void Uniform::Set(int v0, int v1, int v2) {
	throw "ERROR :: CANNOT SET " + mName + " TO INT3";
}

void Uniform::Set(const glm::ivec3 &v) {
	throw "ERROR :: CANNOT SET " + mName + " TO INT3";
}

void Uniform::Set(int v0, int v1, int v2, int v3) {
	throw "ERROR :: CANNOT SET " + mName + " TO INT4";
}

void Uniform::Set(const glm::ivec4 &v) {
	throw "ERROR :: CANNOT SET " + mName + " TO INT4";
}

void Uniform::Set(const glm::mat2 &m) {
	throw "ERROR :: CANNOT SET " + mName + " TO MAT2";
}

void Uniform::Set(const glm::mat3 &m) {
	throw "ERROR :: CANNOT SET " + mName + " TO MAT3";
}

void Uniform::Set(const glm::mat4 &m) {
	std::cout << "can't Set uniform " << mName << " to matrix4!" << std::endl;
	exit(-1);
}

void Uniform::Set(Texture2D* tex) {
	std::cout << "can't Set uniform " << mName << " to texture2D!" << std::endl;
	std::exit(-1);
}

Uniform1f::Uniform1f(const std::string& name, GLuint loc) : Uniform{name, loc}, mValue{} { }

void Uniform1f::Set(float value) {
	mValue = value;
}

void Uniform1f::Upload() {
	glUniform1f(mLoc, mValue);
}

Uniform2f::Uniform2f(const std::string& name, GLuint loc) : Uniform{ name, loc }, mValue{} { }

void Uniform2f::Set(float v0, float v1) {
	mValue = { v0, v1 };
}

void Uniform2f::Set(const glm::vec2 &value) {
	mValue = value;
}

void Uniform2f::Upload() {
	glUniform2fv(mLoc, 1, glm::value_ptr(mValue));
}

Uniform3f::Uniform3f(const std::string& name, GLuint loc) : Uniform{ name, loc }, mValue{} { }

void Uniform3f::Set(float v0, float v1, float v2) {
	mValue = { v0, v1, v2 };
}

void Uniform3f::Set(const glm::vec3 &value) {
	mValue = value;
}

void Uniform3f::Upload() {
	glUniform3fv(mLoc, 1, glm::value_ptr(mValue));
}

Uniform4f::Uniform4f(const std::string& name, GLuint loc) : Uniform{ name, loc }, mValue{} { }

void Uniform4f::Set(float v0, float v1, float v2, float v3) {
	mValue = { v0, v1, v2, v3 };
}

void Uniform4f::Set(const glm::vec4 &value) {
	mValue = value;
}

void Uniform4f::Upload() {
	glUniform4fv(mLoc, 1, glm::value_ptr(mValue));
}

Uniform1i::Uniform1i(const std::string& name, GLuint loc) : Uniform{ name, loc }, mValue{} { }

void Uniform1i::Set(int value) {
	mValue = value;
}

void Uniform1i::Upload() {
	glUniform1i(mLoc, mValue);
}

Uniform2i::Uniform2i(const std::string& name, GLuint loc) : Uniform{ name, loc }, mValue{} { }

void Uniform2i::Set(int v0, int v1) {
	mValue = { v0, v1 };
}

void Uniform2i::Set(const glm::ivec2 &value) {
	mValue = value;
}

void Uniform2i::Upload() {
	glUniform2iv(mLoc, 1, glm::value_ptr(mValue));
}

Uniform3i::Uniform3i(const std::string& name, GLuint loc) : Uniform{name, loc}, mValue{} { }

void Uniform3i::Set(int v0, int v1, int v2) {
	mValue = { v0, v1, v2 };
}

void Uniform3i::Set(const glm::ivec3 &value) {
	mValue = value;
}

void Uniform3i::Upload() {
	glUniform3iv(mLoc, 1, glm::value_ptr(mValue));
}

Uniform4i::Uniform4i(const std::string& name, GLuint loc) : Uniform{name, loc}, mValue{} { }

void Uniform4i::Set(int v0, int v1, int v2, int v3) {
	mValue = { v0, v1, v2, v3 };
}

void Uniform4i::Set(const glm::ivec4 &value) {
	mValue = value;
}

void Uniform4i::Upload() {
	glUniform4iv(mLoc, 1, glm::value_ptr(mValue));
}

UniformMat2::UniformMat2(const std::string& name, GLuint loc) : Uniform{name, loc}, mValue{} { }

void UniformMat2::Set(const glm::mat2& value) {
	mValue = value;
}

void UniformMat2::Upload() {
	glUniformMatrix2fv(mLoc, 1, GL_FALSE, glm::value_ptr(mValue));
}

UniformMat3::UniformMat3(const std::string& name, GLuint loc) : Uniform{name, loc}, mValue{} { }

void UniformMat3::Set(const glm::mat3& value) {
	mValue = value;
}

void UniformMat3::Upload() {
	glUniformMatrix3fv(mLoc, 1, GL_FALSE, glm::value_ptr(mValue));
}

UniformMat4::UniformMat4(const std::string& name, GLuint loc) : Uniform{name, loc} { }

void UniformMat4::Set(const glm::mat4& value) {
	mValue = value;
}

void UniformMat4::Upload() {
	glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mValue));
}

UniformTexture2D::UniformTexture2D(const std::string& name, GLuint loc) : Uniform(name, loc), mpValue{} { }

void UniformTexture2D::Set(Texture2D* pValue) {
	mpValue = pValue;
}

void UniformTexture2D::Upload() {
	mpValue->Enable();
}