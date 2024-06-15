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
}

void init_snake(Game* g) {
	// specify shaders we want to use 
	Shader* vcs = g->add_shader("Vertex Color Shader");

	const char* vertex_src = "#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"layout (location=1) in vec3 aColor;\n"
		"out vec3 vColor;\n"
		"uniform mat4 uMVP;\n"
		"void main() {\n"
		"	gl_Position = uMVP*vec4(aPos, 1.0f);\n"
		"	vColor = aColor;\n"
		"}";

	const char* fragment_src = "#version 330 core\n"
		"in vec3 vColor;\n"
		"out vec4 diffuse_color;\n"
		"uniform vec3 uColor;\n"
		"void main() {\n"
		"	diffuse_color = vec4(uColor * vColor, 1.0f);\n"
		"}";

	vcs->vertex(vertex_src);
	vcs->fragment(fragment_src);
	vcs->compile();

	Shader* scs = g->add_shader("Solid Color Shader");

	vertex_src = "#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"uniform mat4 uMVP;\n"
		"void main() {\n"
		"	gl_Position = uMVP*vec4(aPos, 1.0f);\n"
		"}";

	fragment_src = "#version 330 core\n"
		"out vec4 diffuse_color;\n"
		"uniform vec3 uColor;\n"
		"void main() {\n"
		"	diffuse_color = vec4(uColor, 1.0f);\n"
		"}";

	scs->vertex(vertex_src);
	scs->fragment(fragment_src);
	scs->compile();

	// specify models we want to use

	Model* m = g->add_model("Rectangle");

	VertexData aPos = {
		{-0.5f, 0.5f, 0.0f},   // top left
		{-0.5f, -0.5f, 0.0f},  // bottom left
		{0.5, -0.5f, 0.0f},   // bottom right
		{-0.5f, 0.5f, 0.0f},   // top left
		{0.5f, 0.5f, 0.0f},    // top right
		{0.5f, -0.5f, 0.0f}    // bottom right
	};

	VertexData aColor = {
		{1.0f, 0.0f, 0.0f},  // top left (red)
		{0.0f, 1.0f, 0.0f},  // bottom left (green)
		{0.0f, 0.0f, 1.0f},  // bottom right (blue)
		{1.0f, 0.0f, 0.0f},  // top left (red)
		{1.0f, 1.0f, 0.0f},  // top right (yellow)
		{0.0f, 0.0f, 1.0f}   // bottom right (blue)
	};

	m->vertex_attrib(0, aPos);
	m->vertex_attrib(1, aColor);
	m->compile();

	// specify gameobjects we want to use

	GameObject* sq = g->add_gameobject("Rectangle");
	GameObject* c = g->add_gameobject("Main Camera");

	c->add_component<Transform>();
	Camera* cc = c->add_component<Camera>();

	Transform *t = sq->add_component<Transform>();
	ShaderComponent* sc = sq->add_component<ShaderComponent>();
	ModelComponent* mc = sq->add_component<ModelComponent>();
	Orthographic* pc = sq->add_component<Orthographic>();
	sq->add_component<Controller>();

	sc->add_updater(uniform_updater);

	// alternatively,
	// auto scr = sq->add_component<SolidColorRenderer>();
	// auto sqm = sq->add_component<SquareMesh>();

	cc->add_viewable(sq);

	//Shader* theShader = g->shader("Solid Color Shader");
	//std::cout << "solid color shader has " << theShader->uniforms.size() << " uniforms" << std::endl;

	//Shader* theOtherShader = g->shader("Vertex Color Shader");
	//std::cout << "vertex color shader has " << theOtherShader->uniforms.size() << " uniforms" << std::endl;

	sc->set_shader(g->shader("Vertex Color Shader"));

	sc->set_uniform("uColor", glm::vec3{ 1.0f, 1.0f, 1.0f });
	mc->set_model(g->model("Rectangle"));

	//t->translate(0.5f, 0.0f, 0.0f);
	//t->scale(2.0f, 1.0f, 1.0f);
}

void deinit_snake(Game* g) {

}