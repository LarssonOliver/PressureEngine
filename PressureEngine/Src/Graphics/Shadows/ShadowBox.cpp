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
		Matrix4f rotation = calculateCameraRotationMatrix();
		Vector3f forwardVector(rotation.transform(FORWARD).getXYZ());

		Vector3f toFar(forwardVector);
		toFar.scale(SHADOW_DISTANCE);
		Vector3f toNear(forwardVector);
		toNear.scale(PRESSRE_NEAR_PLANE);
		Vector3f centerNear;
		toNear.add(cam.getPosition(), centerNear);
		Vector3f centerFar;
		toFar.add(cam.getPosition(), centerFar);

		std::vector<Vector4f> points = calculateFrustumVertices(rotation, forwardVector, centerNear, centerFar);

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

	// https://www.dropbox.com/sh/g9vnfiubdglojuh/AACpq1KDpdmB8ZInYxhsKj2Ma/shadows?dl=0&preview=ShadowBox.java


}

