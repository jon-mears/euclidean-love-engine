#include "shader.hpp"

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

#include "factories.hpp"
#include "uniform.hpp"

#include "mesh.hpp"
#include "glsl-translator.hpp"
#include "vertex-data.hpp"

Shader::Shader() : mID{}, mVSource{}, mFSource{}, mUniformCodes{}, mAttribName2Type{}, mAttribName2Loc{} { }

void Shader::Enable() {
	glUseProgram(mID);
}

void Shader::Disable() {
	glUseProgram(0);
}

void Shader::ProvideVertexSource(const std::string& rcSource) {
	char infoLog[512];
	GLint success;

	std::istringstream stream(rcSource);

	std::string word{ "" }, type{ "" }, name{ "" };
	Uniform::Purpose eCurPurpose{ Uniform::NONE };

	while (stream && word != "main") {
		stream >> word;

		if (word == "@MVP_MATRIX") {
			eCurPurpose = Uniform::MVP_MATRIX;
		}

		else if (word == "@M_MATRIX") {
			eCurPurpose = Uniform::M_MATRIX;
		}

		else if (word == "@V_MATRIX") {
			eCurPurpose = Uniform::V_MATRIX;
		}

		else if (word == "@P_MATRIX") {
			eCurPurpose = Uniform::P_MATRIX;
		}

		else if (word == "@MV_MATRIX") {
			eCurPurpose = Uniform::MV_MATRIX;
		}

		else if (word == "@VP_MATRIX") {
			eCurPurpose = Uniform::VP_MATRIX;
		}

		else if (word == "uniform") {
			stream >> type;
			stream >> name;
			std::string::iterator it = std::find_if(name.begin(), name.end(),
				[](char c) {
					return std::ispunct(c);
				});

			name = std::string(name.begin(), it);

			mUniformName2Purpose[name] = eCurPurpose;

			eCurPurpose = Uniform::NONE;
		}
	}

	mVSource = GLSLTranslator::Translate(rcSource);

	const char* vsource = mVSource.c_str();

	mVShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(mVShaderID, 1, &vsource, nullptr);
	glCompileShader(mVShaderID);

	glGetShaderiv(mVShaderID, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(mVShaderID, 512, nullptr, infoLog);
		std::cerr << "ERROR COMPILING VERTEX SHADER\n" << infoLog << std::endl;
		std::exit(-1);
	}
}

void Shader::ProvideFragmentSource(const std::string& rcSource) {
	char infoLog[512];
	GLint success;

	std::istringstream stream(rcSource);

	std::string word{ "" }, type{ "" }, name{ "" };
	Uniform::Purpose eCurPurpose{ Uniform::NONE };

	while (stream && word != "main") {
		stream >> word;

		if (word == "@MVP_MATRIX") {
			eCurPurpose = Uniform::MVP_MATRIX;
		}

		else if (word == "@M_MATRIX") {
			eCurPurpose = Uniform::M_MATRIX;
		}

		else if (word == "@V_MATRIX") {
			eCurPurpose = Uniform::V_MATRIX;
		}

		else if (word == "@P_MATRIX") {
			eCurPurpose = Uniform::P_MATRIX;
		}

		else if (word == "@MV_MATRIX") {
			eCurPurpose = Uniform::MV_MATRIX;
		}

		else if (word == "@VP_MATRIX") {
			eCurPurpose = Uniform::VP_MATRIX;
		}

		else if (word == "uniform") {
			stream >> type;
			stream >> name;
			std::string::iterator it = std::find_if(name.begin(), name.end(),
				[](char c) {
					return std::ispunct(c);
				});

			name = std::string(name.begin(), it);

			mUniformName2Purpose[name] = eCurPurpose;

			eCurPurpose = Uniform::NONE;
		}
	}

	mFSource = GLSLTranslator::Translate(rcSource);

	const char* fsource = mFSource.c_str();

	mFShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(mFShaderID, 1, &fsource, nullptr);
	glCompileShader(mFShaderID);

	glGetShaderiv(mFShaderID, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(mFShaderID, 512, nullptr, infoLog);
		std::cerr << "ERROR COMPILING FRAGMENT SHADER\n" << infoLog << std::endl;
		std::exit(-1);
	}
}

void Shader::Compile() {

	char infoLog[512];
	GLint success;

	mID = glCreateProgram();

	glAttachShader(mID, mVShaderID);
	glAttachShader(mID, mFShaderID);

	glLinkProgram(mID);
	glGetProgramiv(mID, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(mID, 512, nullptr, infoLog);
		std::cerr << "ERROR LINKING PROGRAM\n" << infoLog << std::endl;
		std::exit(-1);
	}	

	std::string word, type, var;

	std::istringstream vertexStream(mVSource);
	while (vertexStream && word != "main") {
		vertexStream >> word;

		if (word == "uniform") {
			vertexStream >> type;
			vertexStream >> var;
			var = var.substr(0, var.size() - 1); // get rid of semicolon at end

			GLuint loc = glGetUniformLocation(mID, var.c_str());

			mUniformCodes.push_back(Uniform::Encode(var, loc, type, 
				mUniformName2Purpose[var]));
		}

		if (word == "in") {
			vertexStream >> type;
			vertexStream >> var;
			var = var.substr(0, var.size() - 1); // get rid of semicolon at end
			GLuint loc = glGetAttribLocation(mID, var.c_str());

			mAttribName2Loc[var] = loc;
			mAttribName2Type[var] = Vertex::Attribute::NONE;
		}
	}

	std::istringstream fragmentStream(mFSource);
	while (fragmentStream && word != "main") {
		fragmentStream >> word;

		if (word == "uniform") {
			fragmentStream >> type;
			fragmentStream >> var;

			if (var.find(';') != std::string::npos) {
				var = var.substr(0, var.size() - 1); // get rid of semicolon at end
			}

			GLuint loc = glGetUniformLocation(mID, var.c_str());

			mUniformCodes.push_back(Uniform::Encode(var, loc, type, 
				mUniformName2Purpose[var]));
		}
	}
}

std::vector<std::string> &Shader::UniformCodes() {
	return mUniformCodes;
}

void Shader::LabelAttrib(const std::string& name, Vertex::Attribute eAttrib) {
	mAttribName2Type[name] = eAttrib;
}