#pragma once

#include "../../DllExport.h"
#include "VertexBufferLayout.h"

namespace Pressure {

	class PRESSURE_API VertexArray {

	private:
		unsigned int m_ID;
		VertexBufferLayout m_Layout;

	public:
		VertexArray(); 

		void bind() const;
		void unbind() const;
		void del() const;
		unsigned int getID() const;

		void bindLayout(const VertexBufferLayout& layout);
		
	};

}