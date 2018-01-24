#pragma once

#include "VertexBufferLayout.h"

namespace Pressure {

	class VertexArray {

	private:
		unsigned int m_ID;
		VertexBufferLayout m_Layout;

	public:
		VertexArray(); 
		~VertexArray();

		void bind() const;
		void unbind() const;

		void bindLayout(const VertexBufferLayout& layout);
		
	};

}