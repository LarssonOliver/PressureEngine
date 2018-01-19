#pragma once

namespace Pressure {

	class IndexBuffer {

	private:
		unsigned int m_ID;
		unsigned int m_Count;

	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline unsigned int count() const { return m_Count; }

	};

}