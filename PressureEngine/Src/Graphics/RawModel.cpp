#include "RawModel.h"

namespace Pressure {

	RawModel::RawModel(const unsigned int vaoID, const int vertexCount) {
		this->vaoID = vaoID;
		this->vertexCount = vertexCount;
	}

	unsigned int RawModel::getVaoID() const {
		return vaoID;
	}

	int RawModel::getVertexCount() const {
		return vertexCount;
	}

}
