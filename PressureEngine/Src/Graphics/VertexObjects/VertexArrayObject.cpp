#include "VertexArrayObject.h"
#include "../../Common.h"

namespace Pressure {

	unsigned int VertexArrayObject::getID() const {
		return ID;
	}

	bool VertexArrayObject::isCreated() const {
		return created;
	}

	unsigned int VertexArrayObject::generate() {
		glGenVertexArrays(1, &ID);
		created = true;
		return ID;
	}

	void VertexArrayObject::bind() const {
		glBindVertexArray(ID);
	}

	void VertexArrayObject::unbind() const {
		glBindVertexArray(NULL);
	}

	void VertexArrayObject::cleanUp() {
		if (created)
			glDeleteVertexArrays(1, &ID);
	}

} 