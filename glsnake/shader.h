#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "resource.hpp"

enum class Attribute;
class Uniform;

class Shader : public Resource {
private:
	GLuint program;
	GLuint vshader = -1;
	GLuint fshader = -1;

	std::string mVSource;
	std::string mFSource;

	std::vector<std::string> mUniformCodes;
	std::map<std::string, Attribute> mAttribName2Type;
	std::map<std::string, GLuint> mAttribName2Loc;

public:
	Shader(const std::string& name);
	Shader();

	void vertex(std::string);
	void fragment(std::string);
	void enable();
	void disable();
	void compile();
	std::vector<std::string> &uniform_codes();

	void label_attrib(const std::string& name, Attribute attrib);
};

#endif