#pragma once
#include "VertexObjects\VertexArrayObject.h"

namespace Pressure {

	class RawModel {

	private:
		unsigned int vaoID;
		int vertexCount;

	public:
		RawModel(VertexArrayObject* vao, const int vertexCount);
		unsigned int getVaoID() const;
		int getVertexCount() const;

	};

}
