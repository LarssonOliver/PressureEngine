#include "VertexArray.h"

#include "../GraphicsCommon.h"

namespace Pressure {

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_ID);
	}

	void VertexArray::bind() const {
		glBindVertexArray(m_ID);
	}

	void VertexArray::unbind() const {
		glBindVertexArray(NULL);
	}

	void VertexArray::bindLayout(const VertexBufferLayout& layout) {
		bind();
		m_Layout = layout;
		const auto& elements = m_Layout.getElements();
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			element.buffer.bind();
			glVertexAttribPointer(i, element.count, element.type, element.normalized, 0, 0);			
		}		
	}

}