#include "vertex-data.hpp"
#include "mesh.hpp"

namespace Primitives {
	Mesh* Cube(char fAttribs) {
		Mesh* pMesh = new Mesh();

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

		return pMesh;
	}

	Mesh* Plane(char fAttribs) {
		Mesh* pMesh = new Mesh();

		if (fAttribs & Vertex::POSITION) {
			VertexData aPos = {
				{-0.5f, 0.5f, 0.0f},   // top left
				{-0.5f, -0.5f, 0.0f},  // bottom left
				{0.5, -0.5f, 0.0f},    // bottom right
				{-0.5f, 0.5f, 0.0f},   // top left
				{0.5f, 0.5f, 0.0f},    // top right
				{0.5f, -0.5f, 0.0f}    // bottom right
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

		return pMesh;
	}
}