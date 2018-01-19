#pragma once

namespace Pressure {

	class VertexBuffer {

	private:
		unsigned int m_ID;

	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

	};

}