#include <string>
#include <vector>
#include <map>

#include "mesh.h"
#include "vertexdata.h"
#include "glsltranslator.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

void Mesh::vertex_attrib(int attrib_loc, VertexData vdata, Attribute attrib) {
    if (_num_vertices == -1)
        _num_vertices = vdata.num_vertices();

    else if (_num_vertices != vdata.num_vertices())
        throw "attributes need to have a consistent number of vertices!";

    mAttribLoc2VData[attrib_loc] = vdata;

    if (attrib != Attribute::NONE)
        mAttribType2VData[attrib] = vdata;
}

void Mesh::compile() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	std::vector<float> collected_data = collect_data();
	std::vector<float>::value_type* p = collected_data.data();

	glBufferData(GL_ARRAY_BUFFER, collected_data.size() * sizeof(GLfloat), p, GL_STATIC_DRAW);

    int stride = 0;

    for (std::map<int, VertexData>::iterator it = mAttribLoc2VData.begin(); it != mAttribLoc2VData.end(); ++it) {
        VertexData vdata = it->second;

        stride += sizeof(GLfloat) * vdata.num_components();
    }

    for (std::map<Attribute, VertexData>::iterator it = mAttribType2VData.begin(); it != mAttribType2VData.end(); ++it) {
        VertexData vdata = it->second;

        stride += sizeof(GLfloat) * vdata.num_components();
    }

    int offset = 0;
	
    for (std::map<int, VertexData>::iterator it = mAttribLoc2VData.begin(); it != mAttribLoc2VData.end(); ++it) {
        int attrib_loc = it->first;
        VertexData vdata = it->second;

        glVertexAttribPointer(attrib_loc, vdata.num_components(), GL_FLOAT, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(attrib_loc);

        offset += vdata.num_components() * sizeof(GLfloat);
    }

    for (std::map<Attribute, VertexData>::iterator it = mAttribType2VData.begin(); it != mAttribType2VData.end(); ++it) {
        int attrib_loc = GLSL_Translator::attrib2loc(it->first);
        VertexData vdata = it->second;

        glVertexAttribPointer(attrib_loc, vdata.num_components(), GL_FLOAT, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(attrib_loc);

        offset += vdata.num_components() * sizeof(GLfloat);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::vector<float> Mesh::collect_data() {
    std::vector<float> collected_data;

    for (int vertex_idx = 0; vertex_idx < _num_vertices; ++vertex_idx) {
        for (std::map<int, VertexData>::iterator it = mAttribLoc2VData.begin(); it != mAttribLoc2VData.end(); ++it) {
            VertexData vdata = it->second;
            for (int component_idx = 0; component_idx < vdata.num_components(); ++component_idx) {
                collected_data.push_back(vdata[vdata.num_components() * vertex_idx + component_idx]);
            }
        }
    }

    for (int vertex_idx = 0; vertex_idx < _num_vertices; ++vertex_idx) {
        for (std::map<Attribute, VertexData>::iterator it = mAttribType2VData.begin(); it != mAttribType2VData.end(); ++it) {
            VertexData vdata = it->second;
            for (int component_idx = 0; component_idx < vdata.num_components(); ++component_idx) {
                collected_data.push_back(vdata[vdata.num_components() * vertex_idx + component_idx]);
            }
        }
    }

    return collected_data;
}

int Mesh::num_vertices() {
    return _num_vertices;
}

void Mesh::enable() {
    glBindVertexArray(vao);
}

VertexData Mesh::get_attrib(Attribute attrib) {
    return mAttribType2VData[attrib];
}

void Mesh::vertex_attrib(Attribute attrib, VertexData vdata) {

    if (_num_vertices == -1)
        _num_vertices = vdata.num_vertices();

    else if (_num_vertices != vdata.num_vertices())
        throw "attributes need to have a consistent number of vertices!";

    mAttribType2VData[attrib] = vdata;
}

Mesh::Mesh() : Resource(), vao(), mAttribLoc2VData(), mAttribType2VData() { }
Mesh::Mesh(std::string s) : Resource(s), vao(), mAttribLoc2VData(), mAttribType2VData() { }