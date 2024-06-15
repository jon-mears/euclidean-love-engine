#include <string>
#include <vector>
#include <map>

#include "model.h"
#include "vertexdata.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

void Model::vertex_attrib(int attrib_loc, VertexData vdata) {
    if (_num_vertices == -1)
        _num_vertices = vdata.num_vertices();

    else if (_num_vertices != vdata.num_vertices())
        throw "attributes need to have a consistent number of vertices!";

    data[attrib_loc] = vdata;
}

void Model::compile() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	std::vector<float> collected_data = collect_data();
	std::vector<float>::value_type* p = collected_data.data();

	glBufferData(GL_ARRAY_BUFFER, collected_data.size() * sizeof(GLfloat), p, GL_STATIC_DRAW);

    int stride = 0;

    for (std::map<int, VertexData>::iterator it = data.begin(); it != data.end(); ++it) {
        VertexData vdata = it->second;

        stride += sizeof(GLfloat) * vdata.num_components();
    }

    int offset = 0;
	
    for (std::map<int, VertexData>::iterator it = data.begin(); it != data.end(); ++it) {
        int attrib_loc = it->first;
        VertexData vdata = it->second;

        glVertexAttribPointer(attrib_loc, vdata.num_components(), GL_FLOAT, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(attrib_loc);

        offset += vdata.num_components() * sizeof(GLfloat);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::vector<float> Model::collect_data() {
    std::vector<float> collected_data;

    for (int vertex_idx = 0; vertex_idx < _num_vertices; ++vertex_idx) {
        for (std::map<int, VertexData>::iterator it = data.begin(); it != data.end(); ++it) {
            VertexData vdata = it->second;
            for (int component_idx = 0; component_idx < vdata.num_components(); ++component_idx) {
                collected_data.push_back(vdata[vdata.num_components() * vertex_idx + component_idx]);
            }
        }
    }

    return collected_data;
}

int Model::num_vertices() {
    return _num_vertices;
}

void Model::enable() {
    glBindVertexArray(vao);
}