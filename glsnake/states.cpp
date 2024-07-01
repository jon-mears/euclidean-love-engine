#include "states.h"
#include "game.h"
#include "transform.h"
#include "orthographic.h"
#include "gameobject.h"
#include "camera.h"
#include "shadercomponent.h"
#include "shader.h"
#include "mesh.h"
#include "vertexdata.h"
#include "mesh_component.hpp"
#include "controller.h"
#include "PuckMovement.hpp"
#include "primitives.hpp"
#include "shader.h"
#include "perspective.h"
#include "image2d.hpp"
#include "texture2d.hpp"
#include "resourcemanager.hpp"
#include "input_manager.hpp"
#include "input_test.hpp"
#include "camera_control.hpp"
#include "targeted_camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

const State Init_State = static_cast<State>(0);

void uniform_updater(GameObject* go, Camera* c) {
	ShaderComponent* sc = go->get_component<ShaderComponent>();
	Transform* t = go->get_component<Transform>();
	Orthographic* pc = go->get_component<Orthographic>();

	glm::mat4 model = t->model_matrix();

	glm::mat4 proj = pc->projection_matrix();
	glm::mat4 view = c->view_matrix();

	//std::cout << glm::to_string(view) << std::endl;

	glm::mat4 MVP = proj * view * model;

	sc->set_uniform("uMVP", MVP);
	sc->upload_uniforms();
}

void init_snake(Game* game) {
	// specify shaders we want to use 

	Shader *texture_shader = ResourceManager::instance().retrieve<Shader>("Texture");

	Image2D* box = new Image2D("C:\\assets\\container.jpg");
	Texture2D* texture = new Texture2D();

	texture->set_image(box);
	texture->compile();

	// specify models we want to use

	Mesh* plane = Primitives::cube(static_cast<char>(Attribute::POSITION) | static_cast<char>(Attribute::TEXTURE_COORD));
	plane->compile();
	ResourceManager::instance().add<Mesh>(plane);

	// specify gameobjects we want to use

	GameObject* paddle = new GameObject("Paddle");

	Transform* tpaddle = paddle->add_component<Transform>();
	tpaddle->set_scale(0.25f, 0.25f, 0.25f);
	//tpaddle->set_pos(-0.5f, 0.0f, 0.0f);
	tpaddle->set_window(game->window("Pong"));

	Orthographic *o = paddle->add_component<Orthographic>();

	MeshComponent* model_paddle = paddle->add_component<MeshComponent>();
	model_paddle->set_mesh(plane);

	ShaderComponent* shader_paddle = paddle->add_component<ShaderComponent>();
	shader_paddle->set_shader(texture_shader);
	shader_paddle->set_uniform("uSampler", texture);
	shader_paddle->add_updater(uniform_updater);

	ResourceManager::instance().add<GameObject>(paddle);

	GameObject* camera = new GameObject("Camera");

	Transform* tcamera = camera->add_component<Transform>();
	tcamera->set_window(game->window("Pong"));

	Camera* ccamera = camera->add_component<TargetedCamera>();
	camera->add_component<CameraControl>();
	ccamera->add_viewable(paddle);

	ResourceManager::instance().add<GameObject>(camera);
}

void deinit_snake(Game* game) {

}