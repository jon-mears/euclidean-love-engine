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

typedef void (*UniformUpdater)(GameObject*, Camera*);

class ShaderComponent : public Component {
private:
	Shader* shader;
	std::vector<UniformUpdater> uniform_updaters;
	std::map<std::string, Uniform*> uniforms;

public:
	ShaderComponent(GameObject* gameobject);
	void set_shader(Shader* s);
	virtual void start() override;
	virtual void update() override;
	void add_updater(UniformUpdater uu);
	void update_uniforms(Camera* c);
	void enable();
	void disable();
	void set_uniform(const std::string& name, const glm::mat4 &value);
	void set_uniform(const std::string& name, const glm::vec3& value);
	void upload_uniforms();
};
#endif