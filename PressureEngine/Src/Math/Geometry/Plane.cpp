#include "Plane.h"

namespace Pressure {
	Plane::Plane()
		: m_Normal(0), m_Distance(0) {}

	Plane::Plane(const Vector3f& normal, const float distance)
		: m_Normal(normal), m_Distance(distance) { }

	void Plane::normalize() {
		float scale = 1.0 / m_Normal.length();
		m_Normal.normalize();
		m_Distance *= scale;
	}

	void Plane::setNormal(const Vector3f& normal) {
		m_Normal = normal;
	}

	void Plane::setDistance(const float distance) {
		m_Distance = distance;
	}

	Vector3f Plane::getNormal() const {
		return m_Normal;
	}

	float Plane::getDistance() const {
		return m_Distance;
	}

}