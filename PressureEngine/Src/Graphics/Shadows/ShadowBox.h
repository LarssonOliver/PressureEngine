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
		static const float SHADOW_DISTANCE;

		float minX, maxX;
		float minY, maxY;
		float minZ, maxZ;
		Matrix4f lightViewMatrix;
		Camera& cam;
		Window& window;

		float farHeight, farWidth, nearHeight, nearWidth;

	public:
		ShadowBox(Matrix4f& lightViewMatrix, Camera& camera, Window& window);
		void tick();
		Vector3f& getCenter();

		float getWidth() const;
		float getHeight() const;
		float getLength() const;

	private:
		void calculateFrustumVertices(std::vector<Vector4f>& points, Matrix4f& rotation, Vector3f& forwardVector, Vector3f& centerNear, Vector3f& centerFar);
		void calculateLightSpaceFrustumCorner(Vector4f& point, Vector3f& startPoint, Vector3f& direction, float width);
		void calculateCameraRotationMatrix(Matrix4f& matrix);
		void calculateWidthsAndHeights();
		float getAspectRatio();

	};

}