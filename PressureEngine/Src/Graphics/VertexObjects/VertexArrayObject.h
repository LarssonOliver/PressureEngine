#pragma once
#include "../../Common.h"

namespace Pressure {

	class VertexArrayObject {

	private:
		bool created = false;
		unsigned int ID;

	public:
		VertexArrayObject();
		~VertexArrayObject();

		unsigned int getID() const;
		bool isCreated() const;

		void bind() const;
		void unbind() const;


	};

}