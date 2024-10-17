#ifndef MESH_HPP
#define MESH_HPP

#include <map>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex-data.hpp"
#include "resource.hpp"

namespace Vertex {
	enum Attribute {
		NONE = 0x0001,
		POSITION = 0x0002,
		VERTEX_COLOR = 0x0004,
		TEXTURE_COORD = 0x0008
	};
}


class Mesh {
private:
	GLuint mVAO;

	std::map<int, VertexData> mAttribLoc2VData; // attribute loc to data
	std::map<Vertex::Attribute, VertexData> mAttribType2VData; // attribute type to data

	std::vector<float> CollectData();

	int mNumVertices{ -1 };
	int mPositionAttrib{ -1 };
	int mVertexColorAttrib{ -1 };

public:
	void VertexAttrib(int attrib_loc, VertexData vdata, Vertex::Attribute eAttrib=Vertex::NONE);
	void VertexAttrib(Vertex::Attribute eAttrib, VertexData vdata);
	void Compile();
	void Enable();
	int GetNumVertices();
	VertexData GetAttrib(Vertex::Attribute eAttrib);

	Mesh();

	~Mesh() {
		glDeleteVertexArrays(1, &mVAO);
	}

	inline bool operator==(const Mesh& rcRHS) {
		return mVAO == rcRHS.mVAO;
	}
};

#endif