#pragma once
#include "../../Math/Matrices/Matrix4f.h"
#include "../Entities/Camera.h"
#include "../Window.h"

namespace Pressure {

	class ShadowBox {

	private:
		static const float OFFSET;
		static const Vector4f UP;
		static const Vector4f FORWARD;

		float m_ShadowDistance;
		float m_MinX, m_MaxX;
		float m_MinY, m_MaxY;
		float m_MinZ, m_MaxZ;
		Matrix4f& m_LightViewMatrix;
		Camera& m_Camera;
		Window& m_Window;
		float m_FarHeight, m_FarWidth, m_NearHeight, m_NearWidth;

	public:
		ShadowBox(Matrix4f& lightViewMatrix, Camera& camera, Window& window);
		void tick();
		Vector3f getCenter();
		void setShadowDistance(float distance);

		float getWidth() const;
		float getHeight() const;
		float getLength() const;
		float getShadowDistance() const;

	private:
		void calculateFrustumVertices(std::vector<Vector4f>& points, Matrix4f& rotation, Vector3f& forwardVector, Vector3f& centerNear, Vector3f& centerFar);
		void calculateLightSpaceFrustumCorner(Vector4f& point, Vector3f& startPoint, Vector3f& direction, float width);
		void calculateCameraRotationMatrix(Matrix4f& matrix);
		void calculateWidthsAndHeights();
		float getAspectRatio();

	};

}