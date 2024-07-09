#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "resource.hpp"
#include "vertex-data.hpp"
#include "mesh.hpp"

enum class Attribute;
class Uniform;

class Shader {
private:
	GLuint mID;
	GLuint mVShaderID{ -1 };
	GLuint mFShaderID{ -1 };

	std::string mVSource;
	std::string mFSource;

	std::vector<std::string> mUniformCodes;
	std::map<std::string, Vertex::Attribute> mAttribName2Type;
	std::map<std::string, GLuint> mAttribName2Loc;

public:
	Shader();

	void ProvideVertexSource(const std::string& rcSource);
	void ProvideFragmentSource(const std::string& rcSource);
	void Enable();
	void Disable();
	void Compile();
	std::vector<std::string> &UniformCodes();

	void LabelAttrib(const std::string& name, Vertex::Attribute eAttrib);
};

#endif