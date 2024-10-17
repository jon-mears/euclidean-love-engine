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
					{-0.5f, -0.5f, -0.5f},
					{0.5f, -0.5f, -0.5f},
					{0.5f, 0.5f, -0.5f},
					{0.5f, 0.5f, -0.5f},
					{-0.5f, 0.5f, -0.5f},
					{-0.5f, -0.5f, -0.5f},

					{-0.5f, -0.5f, 0.5f},
					{0.5f, -0.5f, 0.5f},
					{0.5f, 0.5f, 0.5f},
					{0.5f, 0.5f, 0.5f},
					{-0.5f, 0.5f, 0.5f},
					{-0.5f, -0.5f, 0.5f},

					{-0.5f, 0.5f, 0.5f},
					{-0.5f, 0.5f, -0.5f},
					{-0.5f, -0.5f, -0.5f},
					{-0.5f, -0.5f, -0.5f},
					{-0.5f, -0.5f, 0.5f},
					{-0.5f, 0.5f, 0.5f},

					{0.5f, 0.5f, 0.5f},
					{0.5f, 0.5f, -0.5f},
					{0.5f, -0.5f, -0.5f},
					{0.5f, -0.5f, -0.5f},
					{0.5f, -0.5f, 0.5f},
					{0.5f, 0.5f, 0.5f},

					{-0.5f, -0.5f, -0.5f},
					{0.5f, -0.5f, -0.5f},
					{0.5f, -0.5f, 0.5f},
					{0.5f, -0.5f, 0.5f},
					{-0.5f, -0.5f, 0.5f},
					{-0.5f, -0.5f, -0.5f},

					{-0.5f, 0.5f, -0.5f},
					{0.5f, 0.5f, -0.5f},
					{0.5f, 0.5f, 0.5f},
					{0.5f, 0.5f, 0.5f},
					{-0.5f, 0.5f, 0.5f},
					{-0.5f, 0.5f, -0.5f}
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

	Mesh* Plane(char bitmask);

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