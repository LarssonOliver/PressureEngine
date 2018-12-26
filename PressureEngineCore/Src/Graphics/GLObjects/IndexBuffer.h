#pragma once

namespace Pressure {

	class IndexBuffer {

	private:
		unsigned int m_ID;
		unsigned int m_Count;

	public:
		IndexBuffer(const unsigned int* data, const unsigned int count);

		void bind() const;
		void unbind() const;
		void del() const;

		inline unsigned int count() const { return m_Count; }

	};

}