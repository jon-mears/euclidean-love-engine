#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <map>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "shader.hpp"
#include "uniform.hpp"
#include "uniform-holder.hpp"

class Shader;
class Texture2D;
class Uniform;

class Material {
private:
	Shader* const mpShader;
	std::map<std::string, UniformHolder*> mUniforms{};
	std::map<Uniform::Purpose, UniformHolder*> mPurpose2Uniform{};

public:
	Material(Shader* pShader) : mpShader{ pShader } { 
		for (std::map<std::string, Uniform*>::iterator it = mpShader->mName2Uniform.begin();
			it != mpShader->mName2Uniform.end(); ++it) {
			mUniforms[it->first] = UniformHolder::Create(it->second);
			mPurpose2Uniform[it->second->GetPurpose()] = mUniforms[it->first];
		}
	}

	inline Shader* GetShader() {
		return mpShader;
	}

	void Enable();
	void Disable();

	void SetUniform(const std::string& name, const glm::mat4& value);
	void SetUniform(Uniform::Purpose ePurpose, const glm::mat4& value);

	void SetUniform(const std::string& name, const glm::vec3& value);

	void SetUniform(const std::string& name, const glm::vec4& value);

	void SetUniform(const std::string& name, Texture2D* value);

	void UploadUniforms();
};
#endif