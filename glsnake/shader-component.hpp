#ifndef SHADER_COMPONENT_HPP
#define SHADER_COMPONENT_HPP

#include "component.hpp"

#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>

class CameraComponent;
class Shader;
class GameObject;
class Uniform;
class Texture2D;

typedef void (*UniformUpdater)(GameObject*, CameraComponent*);

class ShaderComponent : public Component {
private:
	Shader* mpShader;
	std::vector<UniformUpdater> mUniformUpdaters;
	std::map<std::string, Uniform*> mUniforms;

public:
	ShaderComponent(GameObject* pGO);
	void SetShader(Shader* pShader);
	virtual void Start() override;
	virtual void Update() override;
	void AddUpdater(UniformUpdater uu);
	void UpdateUniforms(CameraComponent* pCamera);
	void Enable();
	void Disable();
	void SetUniform(const std::string& name, const glm::mat4& value);
	void SetUniform(const std::string& name, const glm::vec3& value);
	void SetUniform(const std::string& name, Texture2D* value);
	void UploadUniforms();
};
#endif