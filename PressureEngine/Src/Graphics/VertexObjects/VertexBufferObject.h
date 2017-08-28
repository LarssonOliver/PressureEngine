#pragma once
#include "../../Common.h"

namespace Pressure {

	class VertexBufferObject {

	private:
		bool created = false;
		unsigned int ID;

	public:
		unsigned int getID() const;
		bool isCreated() const;

		unsigned int generate();
		void bind() const;
		void unbind() const;

		void cleanUp();

	};

}