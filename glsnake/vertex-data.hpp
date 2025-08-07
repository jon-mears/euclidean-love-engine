#ifndef VERTEX_DATA_HPP
#define VERTEX_DATA_HPP
#include <vector>
#include <initializer_list>

class VertexData {
private:
	std::vector<double> mData;
	int mNumVertices = -1;
	int mNumComponents = -1;

public:
	VertexData();
	VertexData(std::initializer_list<double>);
	VertexData(std::initializer_list<std::vector<double>>);

	void AddVertex(const std::initializer_list<double>& rcVertex);

	double& operator[](size_t i);
	std::vector<double>::iterator Begin(); 
	std::vector<double>::iterator End();
	int NumVertices();
	int NumComponents();
};
#endif