#include "Water.h"
#include <vector>

namespace Pressure {

	const int Water::SIZE = 16;
	const int Water::VERTEX_COUNT = 32;

	RawModel* Water::s_Model;

	Water::Water(const Vector3f& position, Loader& loader)
		: m_Position(position) {
		if (!s_Model)
			s_Model = new RawModel(generateWater(loader));
	}

	RawModel Water::getModel() {
		return *Water::s_Model;
	}

	Vector3f& Water::getPosition() {
		return m_Position;
	}

	RawModel Water::generateWater(Loader& loader) {
		int count = VERTEX_COUNT * VERTEX_COUNT;
		std::vector<float> vertices(count * 3);
		int vertexPointer = 0;
		for (int i = 0; i < VERTEX_COUNT; i++) {
			for (int j = 0; j < VERTEX_COUNT; j++) {
				vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
				vertices[vertexPointer * 3 + 1] = 0;
				vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
				vertexPointer++;
			}
		}
		std::vector<unsigned int> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
		int pointer = 0;
		for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
			for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
				int topLeft = (gz * VERTEX_COUNT) + gx;
				//int topRight = topLeft + 1;
				int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
				//int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topLeft + 1;
				indices[pointer++] = topLeft + 1;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomLeft + 1;
			}
		}
		return loader.loadToVao(vertices, indices);
	}

}
