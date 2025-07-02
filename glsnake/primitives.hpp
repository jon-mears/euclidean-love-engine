#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <glm/glm.hpp>

class Mesh;

namespace Primitives {
	template <unsigned char fAttribs>
	Mesh* Cube() {
		static Mesh* pMesh = nullptr;

		if (pMesh == nullptr) {
			pMesh = new Mesh();

			if (fAttribs & Vertex::POSITION) {
				VertexData aPos = {
					{-1.0f, -1.0f, -1.0f},
					{1.0f, -1.0f, -1.0f},
					{1.0f, 1.0f, -1.0f},
					{1.0f, 1.0f, -1.0f},
					{-1.0f, 1.0f, -1.0f},
					{-1.0f, -1.0f, -1.0f},

					{-1.0f, -1.0f, 1.0f},
					{1.0f, -1.0f, 1.0f},
					{1.0f, 1.0f, 1.0f},
					{1.0f, 1.0f, 1.0f},
					{-1.0f, 1.0f, 1.0f},
					{-1.0f, -1.0f, 1.0f},

					{-1.0f, 1.0f, 1.0f},
					{-1.0f, 1.0f, -1.0f},
					{-1.0f, -1.0f, -1.0f},
					{-1.0f, -1.0f, -1.0f},
					{-1.0f, -1.0f, 1.0f},
					{-1.0f, 1.0f, 1.0f},

					{1.0f, 1.0f, 1.0f},
					{1.0f, 1.0f, -1.0f},
					{1.0f, -1.0f, -1.0f},
					{1.0f, -1.0f, -1.0f},
					{1.0f, -1.0f, 1.0f},
					{1.0f, 1.0f, 1.0f},

					{-1.0f, -1.0f, -1.0f},
					{1.0f, -1.0f, -1.0f},
					{1.0f, -1.0f, 1.0f},
					{1.0f, -1.0f, 1.0f},
					{-1.0f, -1.0f, 1.0f},
					{-1.0f, -1.0f, -1.0f},

					{-1.0f, 1.0f, -1.0f},
					{1.0f, 1.0f, -1.0f},
					{1.0f, 1.0f, 1.0f},
					{1.0f, 1.0f, 1.0f},
					{-1.0f, 1.0f, 1.0f},
					{-1.0f, 1.0f, -1.0f}
				};

				pMesh->VertexAttrib(Vertex::POSITION, aPos);
			}

			if (fAttribs & Vertex::TEXTURE_COORD) {
				VertexData aTexCoord = {
					{0.0f, 0.0f},
					{1.0f, 0.0f},
					{1.0f, 1.0f},
					{1.0f, 1.0f},
					{0.0f, 1.0f},
					{0.0f, 0.0f},

					{0.0f, 0.0f},
					{1.0f, 0.0f},
					{1.0f, 1.0f},
					{1.0f, 1.0f},
					{0.0f, 1.0f},
					{0.0f, 0.0f},

					{1.0f, 0.0f},
					{1.0f, 1.0f},
					{0.0f, 1.0f},
					{0.0f, 1.0f},
					{0.0f, 0.0f},
					{1.0f, 0.0f},

					{1.0f, 0.0f},
					{1.0f, 1.0f},
					{0.0f, 1.0f},
					{0.0f, 1.0f},
					{0.0f, 0.0f},
					{1.0f, 0.0f},

					{0.0f, 1.0f},
					{1.0f, 1.0f},
					{1.0f, 0.0f},
					{1.0f, 0.0f},
					{0.0f, 0.0f},
					{0.0f, 1.0f},

					{0.0f, 1.0f},
					{1.0f, 1.0f},
					{1.0f, 0.0f},
					{1.0f, 0.0f},
					{0.0f, 0.0f},
					{0.0f, 1.0f}
				};

				pMesh->VertexAttrib(Vertex::TEXTURE_COORD, aTexCoord);
			}

			pMesh->Compile();
		}

		return pMesh;
	}

	template <unsigned char fAttribs>
	Mesh* Plane() {
		static Mesh* pMesh = nullptr;

		if (pMesh == nullptr) {
			pMesh = new Mesh();

			if (fAttribs & Vertex::POSITION) {
				VertexData aPos = {
					{-1.0f, 1.0f, 0.0f},   // top left
					{-1.0f, -1.0f, 0.0f},  // bottom left
					{1.0f, -1.0f, 0.0f},    // bottom right
					{-1.0f, 1.0f, 0.0f},   // top left
					{1.0f, 1.0f, 0.0f},    // top right
					{1.0f, -1.0f, 0.0f}    // bottom right
				};

				pMesh->VertexAttrib(Vertex::POSITION, aPos);
			}

			if (fAttribs & Vertex::TEXTURE_COORD) {
				VertexData aTexCoord = {
					{0.0f, 1.0f}, // top left
					{0.0f, 0.0f}, // bottom left
					{1.0f, 0.0f}, // bottom right
					{0.0f, 1.0f}, // top left
					{1.0f, 1.0f}, // top right
					{1.0f, 0.0f}  // bottom right
				};

				pMesh->VertexAttrib(Vertex::TEXTURE_COORD, aTexCoord);
			}

			pMesh->Compile();
		}

		return pMesh;
	}

	template <int x, int y, int z>
	Mesh* Line() {
		static Mesh* pMesh = nullptr;

		if (pMesh == nullptr) {
			pMesh = new Mesh();

			VertexData aPos = {
				{0.0f, 0.0f, 0.0f},
				{x, y, z}
			};

			pMesh->VertexAttrib(Vertex::POSITION, aPos);
			pMesh->Compile();
		}

		return pMesh;
	}
}
#endif