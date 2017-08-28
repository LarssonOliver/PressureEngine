#include "VertexBufferObject.h"
#include "../../Common.h"

namespace Pressure {

	VertexBufferObject::VertexBufferObject(GLenum type) {
		this->type = type;
	}

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
		glBindBuffer(type, ID);
	}

	void VertexBufferObject::unbind() const {
		glBindBuffer(type, NULL);
	}

	void VertexBufferObject::cleanUp() {
		if (created)
			glDeleteBuffers(1, &ID);
	}

}