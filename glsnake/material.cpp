#include <iostream>
#include <string>
#include <vector>

#include "material.hpp"
#include "shader.hpp"
#include "uniform.hpp"

void Material::SetShader(Shader* pShader) {
	mpShader = pShader;

	for (std::vector<std::string>::iterator it = pShader->UniformCodes().begin();
		it != pShader->UniformCodes().end(); ++it) {
		Uniform* pUniform = Uniform::Decode(*it);
		mUniforms[pUniform->mName] = pUniform;
	}
}

void Material::Enable() {
	UploadUniforms();
	mpShader->Enable();
}

void Material::Disable() {
	mpShader->Disable();
}

void Material::SetUniform(const std::string& rcName, const glm::mat4& rcValue) {
	if (!mUniforms.count(rcName)) {
		std::cerr << "error :: attempt to access non-existent uniform " << rcName << std::endl;
		exit(-1);
	}

	mUniforms[rcName]->Set(rcValue);
}

void Material::SetUniform(const std::string& rcName, const glm::vec3& rcValue) {
	if (!mUniforms.count(rcName)) {
		std::cerr << "error :: attempt to access non-existent uniform " << rcName << std::endl;
		exit(-1);
	}

	mUniforms[rcName]->Set(rcValue);
}

void Material::SetUniform(const std::string& rcName, Texture2D* pValue) {
	if (!mUniforms.count(rcName)) {
		std::cerr << "error :: attempt to access non-existent uniform " << rcName << std::endl;
		exit(-1);
	}

	mUniforms[rcName]->Set(pValue);
}

void Material::UploadUniforms() {
	mpShader->Enable();
	for (std::pair<const std::string, Uniform*>& rItem : mUniforms) {
		rItem.second->Upload();
	}
	mpShader->Disable();
}