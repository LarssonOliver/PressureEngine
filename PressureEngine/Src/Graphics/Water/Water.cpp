#include "Water.h"
#include <vector>

namespace Pressure {

	using namespace std;

	const int Water::SIZE = 32;
	const int Water::VERTEX_COUNT = 64;

	RawModel Water::model;

	Water::Water(const Vector3f& position, Loader& loader)
		: position(position) {
		if (model.getVertexCount() == 0)
			model = generateWater(loader);
	}

	RawModel Water::getModel() {
		return Water::model;
	}

	Vector3f& Water::getPosition() {
		return position;
	}

	RawModel Water::generateWater(Loader& loader) {
		int count = VERTEX_COUNT * VERTEX_COUNT;
		vector<float> vertices(count * 3);
		int vertexPointer = 0;
		for (int i = 0; i < VERTEX_COUNT; i++) {
			for (int j = 0; j < VERTEX_COUNT; j++) {
				vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
				vertices[vertexPointer * 3 + 1] = 0;
				vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
				vertexPointer++;
			}
		}
		vector<unsigned int> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
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
		return loader.loadToVao(VertexBuffer(&vertices[0], vertices.size() * sizeof(float)), indices);
	}

}
