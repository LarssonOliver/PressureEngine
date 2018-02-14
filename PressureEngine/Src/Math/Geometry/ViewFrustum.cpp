#include "ViewFrustum.h"

namespace Pressure {

	void ViewFrustum::extractPlanes(const Matrix4f& projectionViewMatrix) {
		Vector3f n;

		// Near
		n.setX(projectionViewMatrix.get(0, 3) + projectionViewMatrix.get(0, 2));
		n.setY(projectionViewMatrix.get(1, 3) + projectionViewMatrix.get(1, 2));
		n.setZ(projectionViewMatrix.get(2, 3) + projectionViewMatrix.get(2, 2));
		m_Planes[0].setNormal(n);
		m_Planes[0].setDistance(projectionViewMatrix.get(3, 3) + projectionViewMatrix.get(3, 2));

		// Far
		n.setX(projectionViewMatrix.get(0, 3) - projectionViewMatrix.get(0, 2));
		n.setY(projectionViewMatrix.get(1, 3) - projectionViewMatrix.get(1, 2));
		n.setZ(projectionViewMatrix.get(2, 3) - projectionViewMatrix.get(2, 2));
		m_Planes[1].setNormal(n);
		m_Planes[1].setDistance(projectionViewMatrix.get(3, 3) - projectionViewMatrix.get(3, 2));

		// Left
		n.setX(projectionViewMatrix.get(0, 3) + projectionViewMatrix.get(0, 0));
		n.setY(projectionViewMatrix.get(1, 3) + projectionViewMatrix.get(1, 0));
		n.setZ(projectionViewMatrix.get(2, 3) + projectionViewMatrix.get(2, 0));
		m_Planes[2].setNormal(n);
		m_Planes[2].setDistance(projectionViewMatrix.get(3, 3) + projectionViewMatrix.get(3, 0));

		// Right
		n.setX(projectionViewMatrix.get(0, 3) - projectionViewMatrix.get(0, 0));
		n.setY(projectionViewMatrix.get(1, 3) - projectionViewMatrix.get(1, 0));
		n.setZ(projectionViewMatrix.get(2, 3) - projectionViewMatrix.get(2, 0));
		m_Planes[3].setNormal(n);
		m_Planes[3].setDistance(projectionViewMatrix.get(3, 3) - projectionViewMatrix.get(3, 0));

		// Up
		n.setX(projectionViewMatrix.get(0, 3) - projectionViewMatrix.get(0, 1));
		n.setY(projectionViewMatrix.get(1, 3) - projectionViewMatrix.get(1, 1));
		n.setZ(projectionViewMatrix.get(2, 3) - projectionViewMatrix.get(2, 1));
		m_Planes[4].setNormal(n);
		m_Planes[4].setDistance(projectionViewMatrix.get(3, 3) - projectionViewMatrix.get(3, 1));

		// Down
		n.setX(projectionViewMatrix.get(0, 3) + projectionViewMatrix.get(0, 1));
		n.setY(projectionViewMatrix.get(1, 3) + projectionViewMatrix.get(1, 1));
		n.setZ(projectionViewMatrix.get(2, 3) + projectionViewMatrix.get(2, 1));
		m_Planes[5].setNormal(n);
		m_Planes[5].setDistance(projectionViewMatrix.get(3, 3) + projectionViewMatrix.get(3, 1));

		for (Plane& p : m_Planes) {
			p.normalize();
		}

	}

	bool ViewFrustum::pointInFrustum(const Vector3f& point) const {
		return sphereInFrustum(point, 0);
	}

	bool ViewFrustum::sphereInFrustum(const Vector3f center, const float radius) const {
		for (const Plane& p : m_Planes) {
			if ((center.dot(p.getNormal()) + p.getDistance() + radius) < 0)
				return false;
		}
		return true;
	}

	bool ViewFrustum::aabbInFrustum(const AABB& bounds) const {
		Vector3f corners[6];

		corners[0] = Vector3f(bounds.getMax().getX(), bounds.getMax().getY(), bounds.getMin().getZ());
		corners[1] = Vector3f(bounds.getMax().getX(), bounds.getMin().getY(), bounds.getMin().getZ());
		corners[2] = Vector3f(bounds.getMax().getX(), bounds.getMin().getY(), bounds.getMax().getZ());
		corners[3] = Vector3f(bounds.getMin().getX(), bounds.getMax().getY(), bounds.getMin().getZ());
		corners[4] = Vector3f(bounds.getMin().getX(), bounds.getMin().getY(), bounds.getMin().getZ());
		corners[5] = Vector3f(bounds.getMin().getX(), bounds.getMin().getY(), bounds.getMax().getZ());

		
		if (pointInFrustum(bounds.getMin()) || pointInFrustum(bounds.getMax())) {
			return true;
		}

		for (const Vector3f& v : corners) {
			if (pointInFrustum(v)) return true;
		}

		return false;
	}

}