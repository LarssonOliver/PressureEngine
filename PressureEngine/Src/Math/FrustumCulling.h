#pragma once

#include "Matrices\Matrix4f.h"
#include "Box.h"
#include "../Constants.h"

namespace Pressure {

	class FrustumCulling {

	private:
		static Box m_Frustum;

	public:
		static bool pointInFrustum(const Vector3f& point, const Matrix4f& transformationMatrix, const Matrix4f& viewMatrix, const Matrix4f& projectionMatrix);
		static bool sphereInFrustum(const Vector3f& center, const float radius, const Matrix4f& transformationMatrix, const Matrix4f& viewMatrix, const Matrix4f& projectionMatrix);
		static bool boxInFrustum(const Box& box, const Matrix4f& transformationMatrix, const Matrix4f& viewMatrix, const Matrix4f& projectionMatrix);

	};

}