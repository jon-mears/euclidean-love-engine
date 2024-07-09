#include "shader-component.hpp"
#include "shader.hpp"
#include "game-object.hpp"
#include "camera-component.hpp"
#include "uniform.hpp"
#include "component.hpp"

#include <string>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include "imgui.h"

ShaderComponent::ShaderComponent(GameObject* pGO) : Component{ pGO }, mpShader{ nullptr }, mUniformUpdaters{} { }

void ShaderComponent::SetShader(Shader* pShader) {
	mpShader = pShader;

	for (std::vector<std::string>::iterator it = pShader->UniformCodes().begin(); it != pShader->UniformCodes().end(); ++it) {
		Uniform* u = Uniform::Decode(*it);
		mUniforms[u->mName] = u;
	}
}

void ShaderComponent::Start() { }
void ShaderComponent::Update() { }

void ShaderComponent::AddUpdater(UniformUpdater uu) {
	mUniformUpdaters.push_back(uu);
}

void ShaderComponent::UpdateUniforms(CameraComponent* pCamera) {
	for (UniformUpdater uu : mUniformUpdaters)
		uu(mpGO, pCamera);
}

void ShaderComponent::Enable() {
	mpShader->Enable();
}

void ShaderComponent::Disable() {
	mpShader->Disable();
}

void ShaderComponent::SetUniform(const std::string& name, const glm::mat4 &value) {
	if (!mUniforms.count(name)) {
		std::cerr << "error :: attempt to access non-existent uniform " << name << std::endl;
		exit(-1);
	}
	
	mUniforms[name]->Set(value);
}

void ShaderComponent::SetUniform(const std::string& name, const glm::vec3& value) {
	if (!mUniforms.count(name)) {
		std::cerr << "error :: attempt to access non-existent uniform " << name << std::endl;
		std::exit(-1);
	}

	mUniforms[name]->Set(value);
}

void ShaderComponent::SetUniform(const std::string& name, Texture2D* pValue) {
	if (!mUniforms.count(name)) {
		std::cerr << "error :: attempt to access non-existent uniform " << name << std::endl;
		std::exit(-1);
	}

	mUniforms[name]->Set(pValue);
}

void ShaderComponent::UploadUniforms() {
	Enable();
	for (std::pair<const std::string, Uniform*> &item : mUniforms) {
		item.second->Upload();
	}
	Disable();
}