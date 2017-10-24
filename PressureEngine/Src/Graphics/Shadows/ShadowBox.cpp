#include "ShadowBox.h"
#include "../../Constants.h"

namespace Pressure {

	const float ShadowBox::OFFSET = 10;
	const Vector4f ShadowBox::UP(0, 1, 0, 0);
	const Vector4f ShadowBox::FORWARD(0, 0, -1, 0);
	const float ShadowBox::SHADOW_DISTANCE = 100;

	ShadowBox::ShadowBox(Matrix4f& lightViewMatrix, Camera& camera, Window& window)
		: lightViewMatrix(lightViewMatrix), cam(camera), window(window) {
		calculateWidthsAndHeights();
	}

	void ShadowBox::tick() {
		Matrix4f rotation;
		calculateCameraRotationMatrix(rotation);
		Vector3f forwardVector(rotation.transform(FORWARD).getXYZ());

		Vector3f toFar(forwardVector);
		toFar.scale(SHADOW_DISTANCE);
		Vector3f toNear(forwardVector);
		toNear.scale(PRESSRE_NEAR_PLANE);
		Vector3f centerNear;
		toNear.add(cam.getPosition(), centerNear);
		Vector3f centerFar;
		toFar.add(cam.getPosition(), centerFar);

		std::vector<Vector4f> points;
		calculateFrustumVertices(points, rotation, forwardVector, centerNear, centerFar);

		bool first = true;
		for (auto point : points) {
			if (first) {
				minX = point.x;
				maxX = point.x;
				minY = point.y;
				maxY = point.y;
				minZ = point.z;
				maxZ = point.z;
				first = false;
				continue;
			}
			if (point.x > maxX)
				maxX = point.x;
			else if (point.x < minX)
				minX = point.x;
			if (point.y > maxY) 
				maxY = point.y;
			else if (point.y < minY) 
				minY = point.y;
			if (point.z > maxZ) 
				maxZ = point.z;
			else if (point.z < minZ) 
				minZ = point.z;
		}

		maxZ += OFFSET;
	}

	Vector3f& ShadowBox::getCenter() {
		Vector4f cen((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2, 1);
		Matrix4f invertedLight;
		lightViewMatrix.invert(invertedLight);
		return invertedLight.transform(cen, Vector4f()).getXYZ();
	}

	float ShadowBox::getWidth() const {
		return maxX - minX;
	}

	float ShadowBox::getHeight() const {
		return maxY - minY;
	}

	float ShadowBox::getLength() const {
		return maxZ - minZ;
	}

	void ShadowBox::calculateFrustumVertices(std::vector<Vector4f>& points, Matrix4f& rotation, Vector3f& forwardVector, Vector3f& centerNear, Vector3f& centerFar) {
		Vector3f upVector(rotation.transform(UP, Vector4f()).getXYZ());
		Vector3f rightVector(forwardVector.cross(upVector, Vector3f()));
		Vector3f downVector(upVector.negate(Vector3f()));
		Vector3f leftVector(rightVector.negate(Vector3f()));
		Vector3f farTop(Vector3f(upVector.x * farHeight,
			upVector.y * farHeight, upVector.z * farHeight).add(centerFar));
		Vector3f farBottom(Vector3f(downVector.x * farHeight,
			downVector.y * farHeight, downVector.z * farHeight).add(centerFar));
		Vector3f nearTop(Vector3f(upVector.x * nearHeight,
			upVector.y * nearHeight, upVector.z * nearHeight).add(centerNear));
		Vector3f nearBottom(Vector3f(downVector.x * nearHeight,
			downVector.y * nearHeight, downVector.z * nearHeight).add(centerNear));
		points.resize(8);
		calculateLightSpaceFrustumCorner(points[0], farTop, rightVector, farWidth);
		calculateLightSpaceFrustumCorner(points[1], farTop, leftVector, farWidth);
		calculateLightSpaceFrustumCorner(points[2], farBottom, rightVector, farWidth);
		calculateLightSpaceFrustumCorner(points[3], farBottom, leftVector, farWidth);
		calculateLightSpaceFrustumCorner(points[4], nearTop, rightVector, nearWidth);
		calculateLightSpaceFrustumCorner(points[5], nearTop, leftVector, nearWidth);
		calculateLightSpaceFrustumCorner(points[6], nearBottom, rightVector, nearWidth);
		calculateLightSpaceFrustumCorner(points[7], nearBottom, leftVector, nearWidth);
	}

	void ShadowBox::calculateLightSpaceFrustumCorner(Vector4f& point, Vector3f& startPoint, Vector3f& direction, float width) {
		point = (startPoint.add(direction.x * width, direction.y * width, direction.z * width, Vector3f()), 1.f);
		lightViewMatrix.transform(point, point);
	}

	void ShadowBox::calculateCameraRotationMatrix(Matrix4f& matrix) {		
		matrix.rotate((float) Math::toRadians(-cam.getYaw()), Vector3f(0, 1, 0));
		matrix.rotate((float) Math::toRadians(-cam.getPitch()), Vector3f(1, 0, 0));
	}

	void ShadowBox::calculateWidthsAndHeights() {
		farWidth = (float) (SHADOW_DISTANCE * std::tan(Math::toRadians(PRESSRE_FOV)));
		nearWidth = (float) (PRESSRE_NEAR_PLANE * std::tan(Math::toRadians(PRESSRE_FOV)));
		farHeight = farWidth / getAspectRatio();
		nearHeight = nearWidth / getAspectRatio();
	}

	float ShadowBox::getAspectRatio() {
		return (float) window.getWidth() / (float) window.getHeight();
		return 16 / 9;
	}

}