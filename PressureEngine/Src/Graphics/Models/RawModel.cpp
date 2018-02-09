#include "RawModel.h"

namespace Pressure {

	VertexArray& RawModel::getVertexArray() const {
		return (VertexArray&)m_VertexArray;
	}

	unsigned int RawModel::getVertexCount() const {
		return m_VertexCount;
	}

}