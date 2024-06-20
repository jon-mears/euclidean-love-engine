#include "vertexdata.h"
#include "model.h"

namespace Primitives {
	Model* cube(char bitmask) {
		Model* m = new Model();
		m->name("Cube");

		if (bitmask & static_cast<char>(Attribute::POSITION)) {
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

			m->vertex_attrib(Attribute::POSITION, aPos);
		}

		if (bitmask & static_cast<char>(Attribute::TEXTURE_COORD)) {
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

			m->vertex_attrib(Attribute::TEXTURE_COORD, aTexCoord);
		}

		return m;
	}

	Model* plane(char bitmask) {
		Model* m = new Model();
		m->name("Plane");

		if (bitmask & static_cast<char>(Attribute::POSITION)) {
			VertexData aPos = {
				{-0.5f, 0.5f, 0.0f},   // top left
				{-0.5f, -0.5f, 0.0f},  // bottom left
				{0.5, -0.5f, 0.0f},    // bottom right
				{-0.5f, 0.5f, 0.0f},   // top left
				{0.5f, 0.5f, 0.0f},    // top right
				{0.5f, -0.5f, 0.0f}    // bottom right
			};

			m->vertex_attrib(Attribute::POSITION, aPos);
		}

		if (bitmask & static_cast<char>(Attribute::TEXTURE_COORD)) {
			VertexData aTexCoord = {
				{0.0f, 1.0f}, // top left
				{0.0f, 0.0f}, // bottom left
				{1.0f, 0.0f}, // bottom right
				{0.0f, 1.0f}, // top left
				{1.0f, 1.0f}, // top right
				{1.0f, 0.0f}  // bottom right
			};

			m->vertex_attrib(Attribute::TEXTURE_COORD, aTexCoord);
		}

		return m;
	}
}