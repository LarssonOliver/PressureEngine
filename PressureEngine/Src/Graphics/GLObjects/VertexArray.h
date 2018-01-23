#pragma once

#include "..\GraphicsCommon.h"

namespace Pressure {

	class VertexArray {

	private:
		unsigned int m_ID;

	public:
		VertexArray(); 
		~VertexArray();

		void bind() const;
		void unbind() const;

	};

}