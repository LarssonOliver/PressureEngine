#pragma once
#include "../../DllExport.h"
#include "../GLObjects/GLObjects.h"

namespace Pressure {

	class PRESSURE_API RawModel {

	private:
		VertexArray m_VertexArray;
		unsigned int m_VertexCount;

	public:
		RawModel(const VertexArray& va, const unsigned int vertexCount)
			: m_VertexArray(va), m_VertexCount(m_VertexCount) { }
						
		inline VertexArray getVertexArray() const { return m_VertexArray; }
		inline unsigned int getVertexCount() const { return m_VertexCount; }

	};

}
