#pragma once
#include "../../DllExport.h"
#include "../GLObjects/GLObjects.h"
#include "../../Math/Box.h"

namespace Pressure {

	class PRESSURE_API RawModel {

	private:
		VertexArray m_VertexArray;
		unsigned int m_VertexCount;

		Box m_Bounds;
		bool m_WindAffected;

	public:
		RawModel(const VertexArray& va, const unsigned int vertexCount, const Box& bounds)
			: m_VertexArray(va), m_VertexCount(vertexCount), m_Bounds(bounds), m_WindAffected(false) { }
						
		VertexArray& getVertexArray() const;
		unsigned int getVertexCount() const;
		Box getBox() const;

		inline bool isWindAffected() const { return m_WindAffected; }
		inline void setWindAffected(const bool windAffected) { m_WindAffected = windAffected; }

	};

}
