#include "vertex-data.hpp"
#include <initializer_list>
#include <iostream>
#include <vector>

VertexData::VertexData() : mData{} { }

VertexData::VertexData(std::initializer_list<double> il) : mData{} {
    mNumComponents = 1;
    mNumVertices = il.size();

    for (std::initializer_list<double>::iterator it = il.begin(); it != il.end(); ++it) {
        mData.push_back(*it);
    }
}

VertexData::VertexData(std::initializer_list<std::vector<double>> il) : mData() {
    mNumVertices = il.size();

    for (std::initializer_list<std::vector<double>>::iterator vertex_it = il.begin(); vertex_it != il.end(); ++vertex_it) {
        if (mNumComponents == -1) {
            mNumComponents = vertex_it->size();
        }

        else if (vertex_it->size() != mNumComponents) {
            throw "need to supply a consistent count of components per vertex for a given attribute!";
        }

        for (std::vector<double>::const_iterator component_it = vertex_it->begin(); component_it != vertex_it->end(); ++component_it) {
            mData.push_back(*component_it);
        }
    }
}

double& VertexData::operator[](size_t i) {
    return mData[i];
}

std::vector<double>::iterator VertexData::Begin() {
    return mData.begin();
}

std::vector<double>::iterator VertexData::End() {
    return mData.end();
}

int VertexData::NumVertices() {
    return mNumVertices;
}

int VertexData::NumComponents() {
    return mNumComponents;
}

void VertexData::AddVertex(const std::initializer_list<double>& rcVertex) {
    if (mNumComponents == -1) {
        mNumComponents = rcVertex.size();
    }
    
    if (rcVertex.size() != mNumComponents) {
        std::cerr << "incorrect number of components!" << std::endl;
        std::exit(-1);
    }

    for (std::initializer_list<double>::const_iterator it = rcVertex.begin();
        it != rcVertex.end(); ++it) {
        mData.push_back(*it);
    }

    ++mNumVertices;
}