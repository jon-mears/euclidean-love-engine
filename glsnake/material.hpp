#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <map>
#include <string>
#include <glm/glm.hpp>

class Shader;
class Texture2D;
class Uniform;

class Material {
private:
	Shader* mpShader{nullptr};
	std::map<std::string, Uniform*> mUniforms{};
	Uniform* mpMVPMatrix{ nullptr };
	Uniform* mpMMatrix{ nullptr };
	Uniform* mpVMatrix{ nullptr };
	Uniform* mpPMatrix{ nullptr };
	Uniform* mpMVMatrix{ nullptr };
	Uniform* mpVPMatrix{ nullptr };

public:
	void SetShader(Shader* pShader);
	void Enable();
	void Disable();
	void SetUniform(const std::string& name, const glm::mat4& value);
	void SetUniform(const std::string& name, const glm::vec3& value);
	void SetUniform(const std::string& name, Texture2D* value);
	void UploadUniforms();
};
#endif