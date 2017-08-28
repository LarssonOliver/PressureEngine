#pragma once
#include "VertexObjects\VertexArrayObject.h"

namespace Pressure {

	class RawModel {

	private:
		VertexArrayObject* vao;
		int vertexCount;

	public:
		RawModel(VertexArrayObject* vao, const int vertexCount);
		VertexArrayObject* getVao() const;
		unsigned int getVaoID() const;
		int getVertexCount() const;

	};

}
