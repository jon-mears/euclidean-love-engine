#ifndef VERTEX_DATA_HPP
#define VERTEX_DATA_HPP
#include <vector>
#include <initializer_list>

class VertexData {
private:
	std::vector<float> mData;
	int mNumVertices = -1;
	int mNumComponents = -1;

public:
	VertexData();
	VertexData(std::initializer_list<float>);
	VertexData(std::initializer_list<std::vector<float>>);

	float& operator[](size_t i);
	std::vector<float>::iterator Begin(); 
	std::vector<float>::iterator End();
	int NumVertices();
	int NumComponents();
};
#endif