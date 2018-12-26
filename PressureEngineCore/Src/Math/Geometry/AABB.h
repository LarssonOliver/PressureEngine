#pragma once

#include "../Vectors/Vector3f.h"
#include "../../DllExport.h"

namespace Pressure {

	// Axis Aligned Bounding Box.
	class PRESSURE_API AABB {

	private:
		Vector3f m_Min;
		Vector3f m_Max;

	public:
		AABB(const Vector3f& min, const Vector3f& max);

		AABB& scale(const float scalar);
		AABB& transform(const Vector3f& point);

		Vector3f getMin() const;
		Vector3f getMax() const;
		
		Vector3f getCenter() const;

		// Radius of the smallest sphere that can enclose the AABB.
		float getRadius() const;

	};

}