#include "states.h"
#include "game.h"
#include "transform.h"
#include "orthographic.h"
#include "gameobject.h"
#include "camera.h"
#include "shadercomponent.h"
#include "shader.h"
#include "model.h"
#include "vertexdata.h"
#include "modelcomponent.h"
#include "controller.h"
#include "PuckMovement.hpp"
#include "primitives.hpp"
#include "shader.h"
#include "perspective.h"
#include "image2d.hpp"
#include "texture2d.hpp"
#include "resourcemanager.hpp"

#include <glm/glm.hpp>
#include <iostream>

const State Init_State = static_cast<State>(0);

void uniform_updater(GameObject* go, Camera* c) {
	ShaderComponent* sc = go->get_component<ShaderComponent>();
	Transform* t = go->get_component<Transform>();
	Orthographic* pc = go->get_component<Orthographic>();

	glm::mat4 model = t->model_matrix();

	glm::mat4 proj = pc->projection_matrix();
	glm::mat4 view = c->view_matrix();

	glm::mat4 MVP = proj * view * model;

	sc->set_uniform("uMVP", MVP);
	sc->upload_uniforms();
}

void init_snake(Game* game) {
	// specify shaders we want to use 

	ResourceManager& resources = game->resource_manager();

	Shader *texture_shader = resources.retrieve<Shader>("Texture");

	Image2D* box = new Image2D("C:\\assets\\container.jpg");
	Texture2D* texture = new Texture2D();

	texture->set_image(box);
	texture->compile();

	// specify models we want to use

	Model* plane = Primitives::plane(static_cast<char>(Attribute::POSITION) | static_cast<char>(Attribute::TEXTURE_COORD));
	plane->compile();
	game->add_model(plane);

	// specify gameobjects we want to use

	GameObject* paddle = new GameObject();
	paddle->name("Paddle");

	Transform* tpaddle = paddle->add_component<Transform>();
	tpaddle->set_scale(0.25f, 0.25f, 0.25f);
	tpaddle->set_pos(-0.5f, 0.0f, 0.0f);
	tpaddle->set_window(game->window("Pong"));

	paddle->add_component<Orthographic>();

	ModelComponent* model_paddle = paddle->add_component<ModelComponent>();
	model_paddle->set_model(plane);

	ShaderComponent* shader_paddle = paddle->add_component<ShaderComponent>();
	shader_paddle->set_shader(texture_shader);
	shader_paddle->set_uniform("uSampler", texture);
	shader_paddle->add_updater(uniform_updater);

	game->add_gameobject(paddle);

	GameObject* camera = new GameObject();
	camera->name("Camera");

	Transform* tcamera = camera->add_component<Transform>();
	tcamera->set_window(game->window("Pong"));

	Camera* ccamera = camera->add_component<Camera>();
	ccamera->add_viewable(paddle);

	game->add_gameobject(camera);
}

void deinit_snake(Game* game) {

}