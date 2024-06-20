#include "shadercomponent.h"
#include "shader.h"
#include "gameobject.h"
#include "camera.h"
#include "uniform.h"
#include "component.h"

#include <string>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

ShaderComponent::ShaderComponent(GameObject* gameobject) : Component(gameobject), shader(nullptr), uniform_updaters() { }

void ShaderComponent::set_shader(Shader* s) {
	shader = s;

	for (std::vector<std::string>::iterator it = s->uniform_codes().begin(); it != s->uniform_codes().end(); ++it) {
		Uniform* u = Uniform::decode(*it);
		uniforms[u->name] = u;
	}
}

void ShaderComponent::start() { }
void ShaderComponent::update() { }

void ShaderComponent::add_updater(UniformUpdater uu) {
	uniform_updaters.push_back(uu);
}

void ShaderComponent::update_uniforms(Camera* c) {
	for (UniformUpdater uu : uniform_updaters)
		uu(go, c);
}

void ShaderComponent::enable() {
	shader->enable();
}

void ShaderComponent::disable() {
	shader->disable();
}

void ShaderComponent::set_uniform(const std::string& name, const glm::mat4 &value) {
	if (!uniforms.count(name)) {
		std::cout << "error :: attempt to access non-existent uniform " << name << std::endl;
		exit(-1);
	}
	
	uniforms[name]->set(value);
}

void ShaderComponent::set_uniform(const std::string& name, const glm::vec3& value) {
	if (!uniforms.count(name)) {
		std::cout << "error :: attempt to access non-existent uniform " << name << std::endl;
		exit(-1);
	}

	uniforms[name]->set(value);
}

void ShaderComponent::upload_uniforms() {
	enable();
	for (std::pair<const std::string, Uniform*> &item : uniforms) {
		item.second->upload();
	}
	disable();
}