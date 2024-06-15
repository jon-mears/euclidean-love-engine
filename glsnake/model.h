#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertexdata.h"

class Model {
private:
	GLuint vao;

	std::map<int, VertexData> data;
	std::vector<float> collect_data();

	int _num_vertices = -1;

public:
	void vertex_attrib(int attrib_loc, VertexData vdata);
	void compile();
	void enable();
	int num_vertices();
};

#endif