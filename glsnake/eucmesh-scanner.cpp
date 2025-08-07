#include <fstream>
#include <iostream>
#include <string>

#include "eucmesh-scanner.hpp"
#include "mesh.hpp"
#include "vertex-data.hpp"

Mesh* EucmeshScanner::Parse(const std::string& rcFilename) {
	mFile.open(rcFilename, std::ios::in);

	if (!mFile.is_open()) {
		std::cerr << "could not open file!" << std::endl;
		std::exit(-1);
	}

	Mesh* pMesh = new Mesh();

	while (!mFile.eof()) {
		mFile >> mX;
		mFile >> mY;
		mFile >> mZ;

		mVData.AddVertex({ mX, mY, mZ });
	}

	pMesh->VertexAttrib(Vertex::POSITION, mVData);
	pMesh->Compile();

	return pMesh;
}