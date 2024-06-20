#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>

enum class Attribute;
class Uniform;

class Shader {
private:
	GLuint program;
	GLuint vshader = -1;
	GLuint fshader = -1;

	const char *vsource;
	const char *fsource;

	std::string mName;

	std::vector<std::string> mUniformCodes;
	std::map<std::string, Attribute> mAttribName2Type;
	std::map<std::string, GLuint> mAttribName2Loc;

public:
	void vertex(std::string&);
	void fragment(std::string&);
	void enable();
	void disable();
	void compile();
	std::string &name();
	void name(const std::string &name);
	std::vector<std::string> &uniform_codes();

	void label_attrib(const std::string& name, Attribute attrib);
};

#endif