#include "camera.h"
#include "shadercomponent.h"
#include "mesh_component.hpp"
#include "transform.h"
#include "gameobject.h"
#include "component.h"
#include "framebuffer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(GameObject* gameobject) : Component(gameobject), viewables(), mpTransform(NULL) { }

void Camera::start() { 
	mpTransform = get_component<Transform>();
}

void Camera::update() { }

void Camera::add_viewable(GameObject* go) {
	viewables.push_back(go);
}

void Camera::draw() {
	glViewport(0, 0, mWidth, mHeight);
	mpFramebuffer->Enable();

	for (GameObject* viewable : mViewables) {

		// if it's not owned, might be a good idea to return a 
		// const-reference

		ShaderComponent* sc = viewable->Retrieve<ShaderComponent>();
		MeshComponent* mc = viewable->Retrieve<MeshComponent>();

		if (sc == nullptr)
			throw "NEED A SHADERCOMPONENT TO RENDER!!!";
		if (mc == nullptr)
			throw "NEED A MODELCOMPONENT TO RENDER!!!";	

		sc->update_uniforms(this);
		sc->upload_uniforms();

		sc->enable();
		mc->enable();

		glDrawArrays(GL_TRIANGLES, 0, mc->num_vertices());
	}
}

glm::mat4 Camera::view_matrix() {
	glm::vec3 pos = mpTransform->position();
	glm::vec3 rot = mpTransform->rotation();

	glm::mat4 rotation_matrix{ 1 };

	rotation_matrix = glm::rotate(rotation_matrix, rot.x, glm::vec3(1, 0, 0));
	rotation_matrix = glm::rotate(rotation_matrix, rot.y, glm::vec3(0, 1, 0));
	rotation_matrix = glm::rotate(rotation_matrix, rot.z, glm::vec3(0, 0, 1));

	glm::vec4 c{ 0, 0, -1, 0 };

	c = rotation_matrix * c;

	glm::vec3 center{};
	center.x = c.x;
	center.y = c.y;
	center.z = c.z;

	return glm::lookAt(pos, pos + center, glm::vec3(0.0f, 1.0f, 0.0f));
}