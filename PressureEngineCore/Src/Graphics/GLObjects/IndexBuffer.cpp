#include "IndexBuffer.h"

#include "../GraphicsCommon.h"

namespace Pressure {

	IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count) 
		: m_Count(count) {
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int), data, GL_STATIC_DRAW);
	}

	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void IndexBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	}

	void IndexBuffer::del() const {
		glDeleteBuffers(1, &m_ID);
	}

}