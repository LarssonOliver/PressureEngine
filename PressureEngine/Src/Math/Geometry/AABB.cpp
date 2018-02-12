#include "AABB.h"

namespace Pressure {

	AABB::AABB(const Vector3f& min, const Vector3f& max) 
		: m_Min(min), m_Max(max) { }

	AABB& AABB::scale(const float scalar) {
		Vector3f center = getCenter();
		m_Min = m_Min.sub(center, Vector3f()).mul(scalar).add(center);
		m_Max = m_Max.sub(center, Vector3f()).mul(scalar).add(center);
		return *this;
	}

	AABB& AABB::transform(const Vector3f& point) {
		m_Min.add(point);
		m_Max.add(point);
		return *this;
	}

	Vector3f AABB::getMin() const {
		return m_Min;
	}

	Vector3f AABB::getMax() const {
		return m_Max;
	}

	Vector3f AABB::getCenter() const {
		return m_Max.add(m_Min, Vector3f()).div(2);
	}

	float AABB::getRadius() const {
		return m_Max.sub(m_Min, Vector3f()).div(2).length();
	}

}