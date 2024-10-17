#ifndef RENDERER_H
#define RENDERER_H

#include "component.h"
#include "gameobject.h"

#include <string>
#include <vector>
#include "uniform.h"
#include "drawer.h"

class Renderer : public Component {
private:
	GLuint program;
	GLuint vao;
	int num_vertices;
	std::vector<Uniform> uniforms;
public:
	Renderer(GameObject* go) : Component(go) {
		drawer->register_object(this);
	}

	void draw();
};
#endif