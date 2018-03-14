#include "ShadowBox.h"
#include "../../Constants.h"
#include "../../Services/Properties.h"

namespace Pressure {

	const float ShadowBox::OFFSET = 10;
	const Vector4f ShadowBox::UP(0, 1, 0, 0);
	const Vector4f ShadowBox::FORWARD(0, 0, -1, 0);

	ShadowBox::ShadowBox(Matrix4f& lightViewMatrix, Camera& camera, Window& window)
		: m_ShadowDistance(150), m_LightViewMatrix(lightViewMatrix), m_Camera(camera), m_Window(window) {
		calculateWidthsAndHeights();
	}

	void ShadowBox::tick() {
		Matrix4f rotation;
		calculateCameraRotationMatrix(rotation);
		Vector3f forwardVector(rotation.transform(FORWARD, Vector4f()).getXYZ());

		Vector3f toFar(forwardVector);
		toFar.mul(m_ShadowDistance);
		Vector3f toNear(forwardVector);
		toNear.mul(PRESSURE_NEAR_PLANE);
		Vector3f centerNear;
		toNear.add(m_Camera.getPosition(), centerNear);
		Vector3f centerFar;
		toFar.add(m_Camera.getPosition(), centerFar);

		std::vector<Vector4f> points;
		calculateFrustumVertices(points, rotation, forwardVector, centerNear, centerFar);

		bool first = true;
		for (auto& point : points) {
			if (first) {
				m_MinX = point.x;
				m_MaxX = point.x;
				m_MinY = point.y;
				m_MaxY = point.y;
				m_MinZ = point.z;
				m_MaxZ = point.z;
				first = false;
				continue;
			}
			if (point.x > m_MaxX)
				m_MaxX = point.x;
			else if (point.x < m_MinX)
				m_MinX = point.x;
			if (point.y > m_MaxY) 
				m_MaxY = point.y;
			else if (point.y < m_MinY) 
				m_MinY = point.y;
			if (point.z > m_MaxZ) 
				m_MaxZ = point.z;
			else if (point.z < m_MinZ) 
				m_MinZ = point.z;
		}

		m_MaxZ += OFFSET;
	}

	Vector3f ShadowBox::getCenter() {
		Vector4f cen((m_MinX + m_MaxX) / 2, (m_MinY + m_MaxY) / 2, (m_MinZ + m_MaxZ) / 2, 1);
		Matrix4f invertedLight;
		m_LightViewMatrix.invert(invertedLight);
		return invertedLight.transform(cen, Vector4f()).getXYZ();
	}

	void ShadowBox::setShadowDistance(float distance) {
		if (distance != m_ShadowDistance) {
			m_ShadowDistance = distance;
			calculateWidthsAndHeights();
		}
	}

	float ShadowBox::getWidth() const {
		return m_MaxX - m_MinX;
	}

	float ShadowBox::getHeight() const {
		return m_MaxY - m_MinY;
	}

	float ShadowBox::getLength() const {
		return m_MaxZ - m_MinZ;
	}

	float ShadowBox::getShadowDistance() const {
		return m_ShadowDistance;
	}

	void ShadowBox::calculateFrustumVertices(std::vector<Vector4f>& points, Matrix4f& rotation, Vector3f& forwardVector, Vector3f& centerNear, Vector3f& centerFar) {
		Vector3f upVector(rotation.transform(UP, Vector4f()).getXYZ());
		Vector3f rightVector(forwardVector.cross(upVector, Vector3f()));
		Vector3f downVector;
		upVector.negate(downVector);
		Vector3f leftVector;
		rightVector.negate(leftVector);
		Vector3f farTop(Vector3f(upVector.x * m_FarHeight,
			upVector.y * m_FarHeight, upVector.z * m_FarHeight).add(centerFar));
		Vector3f farBottom(Vector3f(downVector.x * m_FarHeight,
			downVector.y * m_FarHeight, downVector.z * m_FarHeight).add(centerFar));
		Vector3f nearTop(Vector3f(upVector.x * m_NearHeight,
			upVector.y * m_NearHeight, upVector.z * m_NearHeight).add(centerNear));
		Vector3f nearBottom(Vector3f(downVector.x * m_NearHeight,
			downVector.y * m_NearHeight, downVector.z * m_NearHeight).add(centerNear));
		points.resize(8);
		calculateLightSpaceFrustumCorner(points[0], farTop, rightVector, m_FarWidth);
		calculateLightSpaceFrustumCorner(points[1], farTop, leftVector, m_FarWidth);
		calculateLightSpaceFrustumCorner(points[2], farBottom, rightVector, m_FarWidth);
		calculateLightSpaceFrustumCorner(points[3], farBottom, leftVector, m_FarWidth);
		calculateLightSpaceFrustumCorner(points[4], nearTop, rightVector, m_NearWidth);
		calculateLightSpaceFrustumCorner(points[5], nearTop, leftVector, m_NearWidth);
		calculateLightSpaceFrustumCorner(points[6], nearBottom, rightVector, m_NearWidth);
		calculateLightSpaceFrustumCorner(points[7], nearBottom, leftVector, m_NearWidth);
	}

	void ShadowBox::calculateLightSpaceFrustumCorner(Vector4f& point, Vector3f& startPoint, Vector3f& direction, float width) {
		point.set(startPoint.add(direction.x * width, direction.y * width, direction.z * width, Vector3f()), 1.f);
		m_LightViewMatrix.transform(point, point);
	}

	void ShadowBox::calculateCameraRotationMatrix(Matrix4f& matrix) {		
		matrix.rotate((float) Math::toRadians(-m_Camera.getYaw()), Vector3f(0, 1, 0));
		matrix.rotate((float) Math::toRadians(-m_Camera.getPitch()), Vector3f(1, 0, 0));
	}

	void ShadowBox::calculateWidthsAndHeights() {
		m_FarWidth = (float) (m_ShadowDistance * std::tan(Math::toRadians(std::stof(Properties::Inst()->get("fov")))));
		m_NearWidth = (float) (PRESSURE_NEAR_PLANE * std::tan(Math::toRadians(std::stof(Properties::Inst()->get("fov")))));
		m_FarHeight = m_FarWidth / getAspectRatio();
		m_NearHeight = m_NearWidth / getAspectRatio();
	}

	float ShadowBox::getAspectRatio() {
		return (float) m_Window.getWidth() / (float) m_Window.getHeight();
		//return 16 / 9;
	}

}