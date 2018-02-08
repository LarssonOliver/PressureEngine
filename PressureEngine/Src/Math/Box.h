#pragma once

#include "Vectors\Vector3f.h"

namespace Pressure {

	class Box {

	private:
		Vector3f m_MinCorner;
		Vector3f m_MaxCorner;

	public:
		Box();
		Box(const Vector3f& minCorner, const Vector3f& maxCorner);
		
		void set(const Vector3f& minCorner, const Vector3f& maxCorner);

		Vector3f getMin() const;
		Vector3f getMax() const;

		bool intersects(const Vector3f& point) const;
		bool intersects(const Vector3f& center, const float radius) const;
		bool intersects(const Box& other) const;

	};

}