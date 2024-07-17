#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <map>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "shader.hpp"
#include "uniform.hpp"

class Shader;
class Texture2D;
class Uniform;

class Material {
private:
	Shader* mpShader;
	std::map<std::string, Uniform*> mUniforms{};
	std::map<Uniform::Purpose, Uniform*> mPurpose2Uniform{};

public:

	Material() : mpShader{ nullptr } { }
	Material(Shader* pShader) : mpShader{ pShader } { 
		for (std::vector<std::string>::iterator it = pShader->UniformCodes().begin();
			it != pShader->UniformCodes().end(); ++it) {
			Uniform* pUniform = Uniform::Decode(*it);
			mUniforms[pUniform->mName] = pUniform;
			mPurpose2Uniform[pUniform->GetPurpose()] = pUniform;
		}
	}

	void SetShader(Shader* pShader);
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