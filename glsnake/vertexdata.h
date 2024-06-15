#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H
#include <vector>
#include <initializer_list>

class VertexData {
private:
	std::vector<float> data;
	int _num_vertices = -1;
	int _num_components = -1;

public:
	VertexData();
	VertexData(std::initializer_list<float>);
	VertexData(std::initializer_list<std::vector<float>>);

	float& operator[](size_t i);
	std::vector<float>::iterator begin(); 
	std::vector<float>::iterator end();
	int num_vertices();
	int num_components();
};
#endif