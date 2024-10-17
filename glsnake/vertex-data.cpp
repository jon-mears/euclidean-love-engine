#include "vertex-data.hpp"
#include <initializer_list>
#include <vector>

VertexData::VertexData() : mData{} { }

VertexData::VertexData(std::initializer_list<float> il) : mData{} {
    mNumComponents = 1;
    mNumVertices = il.size();

    for (std::initializer_list<float>::iterator it = il.begin(); it != il.end(); ++it) {
        mData.push_back(*it);
    }
}

VertexData::VertexData(std::initializer_list<std::vector<float>> il) : mData() {
    mNumVertices = il.size();

    for (std::initializer_list<std::vector<float>>::iterator vertex_it = il.begin(); vertex_it != il.end(); ++vertex_it) {
        if (mNumComponents == -1) {
            mNumComponents = vertex_it->size();
        }

        else if (vertex_it->size() != mNumComponents) {
            throw "need to supply a consistent count of components per vertex for a given attribute!";
        }

        for (std::vector<float>::const_iterator component_it = vertex_it->begin(); component_it != vertex_it->end(); ++component_it) {
            mData.push_back(*component_it);
        }
    }
}

float& VertexData::operator[](size_t i) {
    return mData[i];
}

std::vector<float>::iterator VertexData::Begin() {
    return mData.begin();
}

std::vector<float>::iterator VertexData::End() {
    return mData.end();
}

int VertexData::NumVertices() {
    return mNumVertices;
}

int VertexData::NumComponents() {
    return mNumComponents;
}