#ifndef EUCMESH_SCANNER_HPP
#define EUCMESH_SCANNER_HPP

#include <fstream>
#include <string>
#include <vector>

#include "vertex-data.hpp"

class EucmeshToken;
class Mesh;

class EucmeshScanner {
private:
	int mStart{ 0 }, mCurrent{ 0 };
	double mX{ 0.0 }, mY{ 0.0 }, mZ{ 0.0 };
	std::ifstream mFile{};

	VertexData mVData{};


public:
	Mesh* Parse(const std::string& rcFilename);
};
#endif