#include "vertexdata.h"
#include <initializer_list>
#include <vector>

VertexData::VertexData() : data() { }

VertexData::VertexData(std::initializer_list<float> il) : data() {
    _num_components = 1;
    _num_vertices = il.size();

    for (std::initializer_list<float>::iterator it = il.begin(); it != il.end(); ++it) {
        data.push_back(*it);
    }
}

VertexData::VertexData(std::initializer_list<std::vector<float>> il) : data() {
    _num_vertices = il.size();

    for (std::initializer_list<std::vector<float>>::iterator vertex_it = il.begin(); vertex_it != il.end(); ++vertex_it) {
        if (_num_components == -1)
            _num_components = vertex_it->size();
        else if (vertex_it->size() != _num_components)
            throw "need to supply a consistent count of components per vertex for a given attribute!";

        for (std::vector<float>::const_iterator component_it = vertex_it->begin(); component_it != vertex_it->end(); ++component_it) {
            data.push_back(*component_it);
        }
    }
}

float& VertexData::operator[](size_t i) {
    return data[i];
}

std::vector<float>::iterator VertexData::begin() {
    return data.begin();
}

std::vector<float>::iterator VertexData::end() {
    return data.end();
}

int VertexData::num_vertices() {
    return _num_vertices;
}

int VertexData::num_components() {
    return _num_components;
}