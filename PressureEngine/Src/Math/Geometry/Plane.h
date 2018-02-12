#pragma once

#include "..\Vectors\Vector3f.h"

namespace Pressure {

	class Plane {

	private:
		// The plane's normal.
		Vector3f m_Normal;

		// Distance from origin.
		float m_Distance;

	public:
		Plane();
		Plane(const Vector3f& normal, const float distance);

		// Normalizes the plane.
		void normalize();

		void setNormal(const Vector3f& normal);
		void setDistance(const float distance);

		Vector3f getNormal() const;
		float getDistance() const;

	};

}