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
#include "uniform.hpp"
#include "mesh.hpp"

enum class Attribute;
class Uniform;

class Shader {
private:
	GLuint mID;
	GLuint mVShaderID{ 0 };
	GLuint mFShaderID{ 0 };

	std::string mVSource;
	std::string mFSource;

	std::vector<std::string> mUniformCodes;
	std::map<std::string, Vertex::Attribute> mAttribName2Type;
	std::map<std::string, GLuint> mAttribName2Loc;
	std::map<std::string, Uniform::Purpose> mUniformName2Purpose;

public:
	Shader();

	void ProvideVertexSource(const std::string& rcSource);
	void ProvideFragmentSource(const std::string& rcSource);
	void Enable();
	void Disable();
	void Compile();
	std::vector<std::string> &UniformCodes();

	void LabelAttrib(const std::string& name, Vertex::Attribute eAttrib);

	inline bool operator==(const Shader& rcRHS) {
		return mID == rcRHS.mID;
	}
};

#endif