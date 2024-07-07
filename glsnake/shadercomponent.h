#ifndef SHADER_COMPONENT_H
#define SHADER_COMPONENT_H

#include "component.h"

#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>

class Camera;
class Shader;
class GameObject;
class Camera;
class Uniform;
class Texture2D;

typedef void (*UniformUpdater)(GameObject*, Camera*);

class ShaderComponent : public Component {
private:
	Shader* shader;
	std::vector<UniformUpdater> uniform_updaters;
	std::map<std::string, Uniform*> uniforms;

public:
	ShaderComponent(GameObject* gameobject);
	void SetShader(Shader* s);
	virtual void Start() override;
	virtual void Update() override;
	void add_updater(UniformUpdater uu);
	void update_uniforms(Camera* c);
	void Enable();
	void Disable();
	void SetUniform(const std::string& name, const glm::mat4& value);
	void SetUniform(const std::string& name, const glm::vec3& value);
	void SetUniform(const std::string& name, Texture2D* value);
	void UploadUniforms();
};
#endif