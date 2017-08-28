#include "RawModel.h"

namespace Pressure {

	RawModel::RawModel(VertexArrayObject* vao, const int vertexCount) {
		this->vaoID = vao->getID();
		this->vertexCount = vertexCount;
	}

	unsigned int RawModel::getVaoID() const {
		return vaoID;
	}

	int RawModel::getVertexCount() const {
		return vertexCount;
	}

}
