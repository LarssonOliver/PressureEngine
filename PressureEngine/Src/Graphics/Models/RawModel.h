#pragma once
#include "../../DllExport.h"
#include "../GLObjects/GLObjects.h"

namespace Pressure {

	class PRESSURE_API RawModel {

	private:
		VertexArray m_VertexArray;
		unsigned int m_VertexCount;

		bool m_WindAffected;

	public:
		RawModel(const VertexArray& va, const unsigned int vertexCount)
			: m_VertexArray(va), m_VertexCount(vertexCount), m_WindAffected(false) { }
						
		VertexArray& getVertexArray() const;
		unsigned int getVertexCount() const;

		inline bool isWindAffected() const { return m_WindAffected; }
		inline void setWindAffected(const bool windAffected) { m_WindAffected = windAffected; }

	};

}
