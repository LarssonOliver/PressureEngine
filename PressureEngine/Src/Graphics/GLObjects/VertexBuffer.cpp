#include "VertexBuffer.h"

namespace Pressure {

	VertexBuffer::VertexBuffer(const void* data, const unsigned int size, const unsigned int type)
		: m_Type(type) {
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		if (data != nullptr)
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		else 
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STREAM_DRAW);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_ID);
	}

	void VertexBuffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VertexBuffer::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

	void VertexBuffer::update(const void* data, const unsigned int size) const {
		bind();
		glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		unbind();
	}

	void VertexBuffer::addInstancedAttribute(const unsigned int attribute, const unsigned int size, const unsigned int count, const unsigned int offset) const {
		bind();
		glVertexAttribPointer(attribute, size, m_Type, false, count * sizeof(float), (const void*)(offset * sizeof(float)));
		glVertexAttribDivisor(attribute, 1);
		unbind();
	}

}