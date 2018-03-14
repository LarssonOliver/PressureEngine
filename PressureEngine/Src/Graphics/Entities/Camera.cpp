#include "Camera.h"
#include <cmath>
#include "../../Input/Input.h"
#include "../../Math/Math.h"

namespace Pressure {

	Camera::Camera()
		: m_Position(0), m_Pitch(50), m_Yaw(0), m_Roll(0), m_Anchor(0), m_DistanceFromAnchor(20),
		m_AngleAroundAnchor(0), m_MaxSpeed(0.5f), m_Speed(0), m_Acceleration(0)
	{ }

	Vector3f& Camera::getPosition() {
		return m_Position;
	}

	Vector3f& Camera::getAnchor() {
		return m_Anchor;
	}

	void Camera::tick() {

		static const float acc = 0.05f;

		if (Keyboard::isPressed(GLFW_KEY_W))
			m_Acceleration.setZ(-acc);
		else if (Keyboard::isPressed(GLFW_KEY_S))
			m_Acceleration.setZ(acc);
		else 
			m_Acceleration.setZ(0);
		if (Keyboard::isPressed(GLFW_KEY_W) && Keyboard::isPressed(GLFW_KEY_S))
			m_Acceleration.setZ(0);

		if (Keyboard::isPressed(GLFW_KEY_A))
			m_Acceleration.setX(-acc);
		else if (Keyboard::isPressed(GLFW_KEY_D))
			m_Acceleration.setX(acc);
		else 
			m_Acceleration.setX(0);
		if (Keyboard::isPressed(GLFW_KEY_A) && Keyboard::isPressed(GLFW_KEY_D))
			m_Acceleration.setX(0);

		m_Speed.add(m_Acceleration);
		Math::frange(m_Speed.x, -m_MaxSpeed, m_MaxSpeed);
		Math::frange(m_Speed.y, -m_MaxSpeed, m_MaxSpeed);
		Math::frange(m_Speed.z, -m_MaxSpeed, m_MaxSpeed);
		moveAnchor(m_Speed);

		// Deceleration.
		m_Speed.mul(0.8f);

		calculateZoom();
		calculatePitch();
		calculateAngleAroundAnchor();
		calculateCameraPosition();
	}

	float Camera::getPitch() const {
		return m_Pitch;
	}

	float Camera::getYaw() const {
		return m_Yaw;
	}

	float Camera::getRoll() const {
		return m_Roll;
	}

	void Camera::invertPitch() {
		m_Pitch = -m_Pitch;
	}

	void Camera::setSpeed(const float speed) {
		this->m_MaxSpeed = speed;
	}

	float Camera::getSpeed() const {
		return m_MaxSpeed;
	}

	float Camera::getDistanceFromAnchor() const {
		return m_DistanceFromAnchor;
	}

	float Camera::calculateHorizontalDistance() {
		return m_DistanceFromAnchor * std::cosf((float) Math::toRadians(m_Pitch));
	}

	float Camera::calculateVerticalDistance() {
		return m_DistanceFromAnchor * std::sinf((float) Math::toRadians(m_Pitch));
	}

	void Camera::calculateCameraPosition() {
		float horizontalDistance = calculateHorizontalDistance();
		float verticalDistance = calculateVerticalDistance();
		m_Position.x = m_Anchor.x + horizontalDistance * std::sinf((float) Math::toRadians(m_AngleAroundAnchor));
		m_Position.z = m_Anchor.z + horizontalDistance * std::cosf((float) Math::toRadians(m_AngleAroundAnchor));
		m_Position.y = m_Anchor.y + verticalDistance;
	}

	void Camera::calculateZoom() {
		m_DistanceFromAnchor -= Mouse::getDWheel() * 3;
		Math::frange(m_DistanceFromAnchor, 2, 100);
	}

	void Camera::calculatePitch() {
		if (Mouse::isPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			m_Pitch += Mouse::getDY() * 0.1f;
			Math::frange(m_Pitch, -85, 85);
		}
	}

	void Camera::calculateAngleAroundAnchor() {
		if (Mouse::isPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			m_AngleAroundAnchor -= Mouse::getDX() * 0.3f;

			// Makes sure that the angle always is 0 >= x >= 360
			if (m_AngleAroundAnchor > 360)
				m_AngleAroundAnchor -= 360;
			else if (m_AngleAroundAnchor < 0)
				m_AngleAroundAnchor += 360;

			m_Yaw = -m_AngleAroundAnchor;
		}
	}

	void Camera::moveAnchor(const Vector3f& speed) {
		m_Anchor.x += speed.x * std::sinf((float) Math::toRadians(90 + m_AngleAroundAnchor));
		m_Anchor.z += speed.x * std::cosf((float) Math::toRadians(90 + m_AngleAroundAnchor));

		m_Anchor.x += speed.z * std::sinf((float) Math::toRadians(m_AngleAroundAnchor));
		m_Anchor.z += speed.z * std::cosf((float) Math::toRadians(m_AngleAroundAnchor));

		m_Anchor.y += speed.y;
	}

}