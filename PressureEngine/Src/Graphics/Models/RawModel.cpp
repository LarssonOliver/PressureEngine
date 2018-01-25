#include "RawModel.h"

namespace Pressure {

	VertexArray& Pressure::RawModel::getVertexArray() const {
		return (VertexArray&)m_VertexArray;
	}

	unsigned int RawModel::getVertexCount() const {
		return m_VertexCount;
	}

}