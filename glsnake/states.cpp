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

	Shader* color_shader = new Shader();
	color_shader->name("Color Shader");

	std::string vertex_src = "#version 330 core\n"
		"@POSITION in vec3 aPos;\n"
		"uniform mat4 uMVP;\n"
		"void main() {\n"
		"	gl_Position = uMVP*vec4(aPos, 1.0f);\n"
		"}";

	std::string fragment_src = "#version 330 core\n"
		"out vec4 diffuse_color;\n"
		"uniform vec3 uColor;\n"
		"void main() {\n"
		"	diffuse_color = vec4(uColor, 1.0f);\n"
		"}";

	color_shader->vertex(vertex_src);
	color_shader->fragment(fragment_src);
	color_shader->compile();

	game->add_shader(color_shader);

	// specify models we want to use

	Model* plane = Primitives::plane(static_cast<char>(Attribute::POSITION));
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
	shader_paddle->set_shader(color_shader);
	shader_paddle->set_uniform("uColor", glm::vec3{ 0.0f, 0.0f, 1.0f });
	shader_paddle->add_updater(uniform_updater);

	game->add_gameobject(paddle);

	GameObject* paddle2 = new GameObject();
	paddle2->name("Paddle_2");

	Transform* tpaddle2 = paddle2->add_component<Transform>();
	tpaddle2->set_scale(0.25f, 0.25f, 0.25f);
	tpaddle2->set_pos(0.5f, 0.0f, 0.0f);
	tpaddle2->set_window(game->window("Pong"));

	paddle2->add_component<Orthographic>();

	ModelComponent* model_paddle2 = paddle2->add_component<ModelComponent>();
	model_paddle2->set_model(plane);

	ShaderComponent* shader_paddle2 = paddle2->add_component<ShaderComponent>();
	shader_paddle2->set_shader(color_shader);
	shader_paddle2->set_uniform("uColor", glm::vec3{ 1.0f, 0.0f, 0.0f });
	shader_paddle2->add_updater(uniform_updater);

	game->add_gameobject(paddle2);

	GameObject* camera = new GameObject();
	camera->name("Camera");

	Transform* tcamera = camera->add_component<Transform>();
	tcamera->set_window(game->window("Pong"));

	Camera* ccamera = camera->add_component<Camera>();
	ccamera->add_viewable(paddle);
	ccamera->add_viewable(paddle2);

	game->add_gameobject(camera);
}

void deinit_snake(Game* game) {

}