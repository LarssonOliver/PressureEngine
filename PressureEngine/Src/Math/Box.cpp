#include "Box.h"

namespace Pressure {
	Box::Box()
		: m_MinCorner(Vector3f()), m_MaxCorner(Vector3f()) { }

	Box::Box(const Vector3f& minCorner, const Vector3f& maxCorner)
		: m_MinCorner(minCorner), m_MaxCorner(maxCorner) { }

	void Box::set(const Vector3f& minCorner, const Vector3f& maxCorner) {
		m_MinCorner = minCorner;
		m_MaxCorner = maxCorner;
	}

	Vector3f Box::getMin() const {
		return m_MinCorner;
	}

	Vector3f Box::getMax() const {
		return m_MaxCorner;
	}

	bool Box::intersects(const Vector3f& point) const {
		return (m_MinCorner < point && m_MaxCorner > point);
	}

	bool Box::intersects(const Vector3f& center, const float radius) const {
		return (m_MinCorner < center.sub(radius, Vector3f()) && m_MaxCorner > center.add(radius, Vector3f()));
	}

	bool Box::intersects(const Box& other) const {
		if ((m_MinCorner.getX() < other.getMax().getX() && m_MaxCorner.getX() > other.getMax().getX()) || (m_MinCorner.getX() < other.getMin().getX() && m_MaxCorner.getX() > other.getMin().getX())) {
			if ((m_MinCorner.getY() < other.getMax().getY() && m_MaxCorner.getY() > other.getMax().getY()) || (m_MinCorner.getY() < other.getMin().getY() && m_MaxCorner.getY() > other.getMin().getY())) {
				if ((m_MinCorner.getZ() < other.getMax().getZ() && m_MaxCorner.getZ() > other.getMax().getZ()) || (m_MinCorner.getZ() < other.getMin().getZ() && m_MaxCorner.getZ() > other.getMin().getZ())) {
					return true;
				}
			}
		}
		return false;
	}

}