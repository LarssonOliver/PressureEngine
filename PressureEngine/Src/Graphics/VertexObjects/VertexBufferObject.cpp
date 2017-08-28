#include "VertexBufferObject.h"
#include "../../Common.h"

namespace Pressure {

	unsigned int VertexBufferObject::getID() const {
		return ID;
	}

	bool VertexBufferObject::isCreated() const {
		return created;
	}

	unsigned int VertexBufferObject::generate() {
		glGenBuffers(1, &ID);
		created = true;
		return ID;
	}

	void VertexBufferObject::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VertexBufferObject::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

	void VertexBufferObject::cleanUp() {
		if (created)
			glDeleteBuffers(1, &ID);
	}

}