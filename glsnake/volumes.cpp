#include "mesh.h"
#include "aabb.hpp"
#include "vertexdata.h"

#include <glm/glm.hpp>

namespace Volumes {
	AABB* make_AABB(Mesh* m) {
		VertexData pos_data = m->get_attrib(Attribute::POSITION);
		float minX = pos_data[0], minY = pos_data[1], minZ = pos_data[2];
		float maxX = pos_data[0], maxY = pos_data[1], maxZ = pos_data[2];

		for (int i = 1; i < pos_data.num_vertices(); ++i) {
			float x = pos_data[i * 3 + 0], y = pos_data[i * 3 + 1], z = pos_data[i * 3 + 2];
			if (x < minX)
				minX = x;
			if (y < minY)
				minY = y;
			if (z < minZ)
				minZ = z;
			if (x > maxX)
				maxX = x;
			if (y > maxY)
				maxY = y;
			if (z > maxZ)
				maxZ = z;
		}

		return new AABB(glm::vec3{ minX, minY, minZ }, glm::vec3{ maxX, maxY, maxZ });
	}
}