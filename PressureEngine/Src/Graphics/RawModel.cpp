#include "RawModel.h"

namespace Pressure {

	RawModel::RawModel(VertexArrayObject* vao, const int vertexCount) {
		this->vao = vao;
		this->vertexCount = vertexCount;
	}

	VertexArrayObject* RawModel::getVao() const {
		return vao;
	}

	unsigned int RawModel::getVaoID() const {
		return vao->getID();
	}

	int RawModel::getVertexCount() const {
		return vertexCount;
	}

}
