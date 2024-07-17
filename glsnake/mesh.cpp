#include <string>
#include <vector>
#include <map>

#include "mesh.hpp"
#include "vertex-data.hpp"
#include "glsl-translator.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

void Mesh::VertexAttrib(int attrib_loc, VertexData vdata, Vertex::Attribute eAttrib) {
    if (mNumVertices == -1) {
        mNumVertices = vdata.NumVertices();
    }

    else if (mNumVertices != vdata.NumVertices()) {
        std::cerr << "vertex data must contain the same number of vertices!" << std::endl;
        std::exit(-1);
    }

    mAttribLoc2VData[attrib_loc] = vdata;

    if (eAttrib != Vertex::NONE) {
        mAttribType2VData[eAttrib] = vdata;
    }
}

void Mesh::Compile() {
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	std::vector<float> collected_data = CollectData();
	std::vector<float>::value_type* p = collected_data.data();

	glBufferData(GL_ARRAY_BUFFER, collected_data.size() * sizeof(GLfloat), p, GL_STATIC_DRAW);

    int stride = 0;

    for (std::map<int, VertexData>::iterator it = mAttribLoc2VData.begin(); it != mAttribLoc2VData.end(); ++it) {
        VertexData vdata = it->second;

        stride += sizeof(GLfloat) * vdata.NumComponents();
    }

    for (std::map<Vertex::Attribute, VertexData>::iterator it = mAttribType2VData.begin(); it != mAttribType2VData.end(); ++it) {
        VertexData vdata = it->second;

        stride += sizeof(GLfloat) * vdata.NumComponents();
    }

    int offset = 0;
	
    for (std::map<int, VertexData>::iterator it = mAttribLoc2VData.begin(); it != mAttribLoc2VData.end(); ++it) {
        int attrib_loc = it->first;
        VertexData vdata = it->second;

        glVertexAttribPointer(attrib_loc, vdata.NumComponents(), GL_FLOAT, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(attrib_loc);

        offset += vdata.NumComponents() * sizeof(GLfloat);
    }

    for (std::map<Vertex::Attribute, VertexData>::iterator it = mAttribType2VData.begin(); it != mAttribType2VData.end(); ++it) {
        int attrib_loc = GLSLTranslator::Attrib2Loc(it->first);
        VertexData vdata = it->second;

        glVertexAttribPointer(attrib_loc, vdata.NumComponents(), GL_FLOAT, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(attrib_loc);

        offset += vdata.NumComponents() * sizeof(GLfloat);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::vector<float> Mesh::CollectData() {
    std::vector<float> collected_data;

    for (int vertex_idx = 0; vertex_idx < mNumVertices; ++vertex_idx) {
        for (std::map<int, VertexData>::iterator it = mAttribLoc2VData.begin(); it != mAttribLoc2VData.end(); ++it) {
            VertexData vdata = it->second;
            for (int component_idx = 0; component_idx < vdata.NumComponents(); ++component_idx) {
                collected_data.push_back(vdata[vdata.NumComponents() * vertex_idx + component_idx]);
            }
        }
    }

    for (int vertex_idx = 0; vertex_idx < mNumVertices; ++vertex_idx) {
        for (std::map<Vertex::Attribute, VertexData>::iterator it = mAttribType2VData.begin(); it != mAttribType2VData.end(); ++it) {
            VertexData vdata = it->second;
            for (int component_idx = 0; component_idx < vdata.NumComponents(); ++component_idx) {
                collected_data.push_back(vdata[vdata.NumComponents() * vertex_idx + component_idx]);
            }
        }
    }

    return collected_data;
}

int Mesh::GetNumVertices() {
    return mNumVertices;
}

void Mesh::Enable() {
    glBindVertexArray(mVAO);
}

VertexData Mesh::GetAttrib(Vertex::Attribute eAttrib) {
    return mAttribType2VData[eAttrib];
}

void Mesh::VertexAttrib(Vertex::Attribute eAttrib, VertexData vdata) {

    if (mNumVertices == -1) {
        mNumVertices = vdata.NumVertices();
    }

    else if (mNumVertices != vdata.NumVertices()) {
        std::cerr << "attributes need to have a consistent number of vertices!" << std::endl;
        std::exit(-1);
    }

    mAttribType2VData[eAttrib] = vdata;
}

Mesh::Mesh() : mVAO(), mAttribLoc2VData(), mAttribType2VData() { }