#include "FrustumCulling.h"

namespace Pressure {

	Box FrustumCulling::m_Frustum(Vector3f(-1, -1, PRESSRE_NEAR_PLANE), Vector3f(1, 1, PRESSRE_FAR_PLANE));

	bool FrustumCulling::pointInFrustum(const Vector3f& point, const Matrix4f& transformationMatrix, const Matrix4f& viewMatrix, const Matrix4f& projectionMatrix) {		
		Vector4f res;
		transformationMatrix.transform(Vector4f(point, 1.0), res);
		viewMatrix.transform(res, res);
		projectionMatrix.transform(res, res);
		return m_Frustum.intersects(res.getXYZ());
	}

	bool FrustumCulling::sphereInFrustum(const Vector3f& center, const float radius, const Matrix4f& transformationMatrix, const Matrix4f& viewMatrix, const Matrix4f& projectionMatrix) {
		Vector4f res;
		transformationMatrix.transform(Vector4f(center, 1.0), res);
		viewMatrix.transform(res, res);
		projectionMatrix.transform(res, res);
		return m_Frustum.intersects(res.getXYZ(), radius);
	}

	bool FrustumCulling::boxInFrustum(const Box& box, const Matrix4f& transformationMatrix, const Matrix4f& viewMatrix, const Matrix4f& projectionMatrix) {
		Vector4f max(box.getMax(), 1.0);
		Vector4f min(box.getMin(), 1.0);
		transformationMatrix.transform(max, max);
		transformationMatrix.transform(min, min);
		viewMatrix.transform(max, max);
		viewMatrix.transform(min, min);
		projectionMatrix.transform(max, max);
		projectionMatrix.transform(min, min);
		return Box(projectionMatrix.transform(Vector4f(box.getMin(), 1.0), Vector4f()).getXYZ(), projectionMatrix.transform(Vector4f(box.getMax(), 1.0), Vector4f()).getXYZ()).intersects(Box(min.getXYZ(), max.getXYZ()));
	}

}