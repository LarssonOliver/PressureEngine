#include "Camera.h"
#include <cmath>
#include "../../Input/Input.h"
#include "../../Math/Math.h"

namespace Pressure {

	Camera::Camera()
		: position(0), pitch(0), yaw(0), roll(0), anchor(0), distanceFromAnchor(5), angleAroundAnchor(0), speed(0.5f)
	{ }

	Vector3f& Camera::getPosition() {
		return position;
	}

	Vector3f& Camera::getAnchor() {
		return anchor;
	}

	void Camera::tick() {
		calculateZoom();
		calculatePitch();
		calculateAngleAroundAnchor();
		calculateCameraPosition();		

		if (Keyboard::isPressed(GLFW_KEY_W))
			moveAnchor(0, 0, -speed);
		if (Keyboard::isPressed(GLFW_KEY_S))
			moveAnchor(0, 0, speed);
		if (Keyboard::isPressed(GLFW_KEY_A))
			moveAnchor(-speed, 0, 0);
		if (Keyboard::isPressed(GLFW_KEY_D))
			moveAnchor(speed, 0, 0);
		//if (Keyboard::isPressed(GLFW_KEY_SPACE))
			//anchor.add(0, speed, 0);
		//if (Keyboard::isPressed(GLFW_KEY_Z))
			//anchor.add(0, -speed, 0);
	}

	float Camera::getPitch() const {
		return pitch;
	}

	float Camera::getYaw() const {
		return yaw;
	}

	float Camera::getRoll() const {
		return roll;
	}

	void Camera::setSpeed(const float speed) {
		this->speed = speed;
	}

	float Camera::getSpeed() const {
		return speed;
	}

	float Camera::calculateHorizontalDistance() {
		return distanceFromAnchor * std::cosf(Math::toRadians(pitch));
	}

	float Camera::calculateVerticalDistance() {
		return distanceFromAnchor * std::sinf(Math::toRadians(pitch));
	}

	void Camera::calculateCameraPosition() {
		float horizontalDistance = calculateHorizontalDistance();
		float verticalDistance = calculateVerticalDistance();

		float xoffset = horizontalDistance * std::sinf(Math::toRadians(angleAroundAnchor));
		float zoffset = horizontalDistance * std::cosf(Math::toRadians(angleAroundAnchor));
		position.x = anchor.x + xoffset;
		position.z = anchor.z + zoffset;
		position.y = anchor.y + verticalDistance;
	}

	void Camera::calculateZoom() {
		distanceFromAnchor -= Mouse::getDWheel();
		Math::frange(distanceFromAnchor, 2, 50);
	}

	void Camera::calculatePitch() {
		if (Mouse::isPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			pitch += Mouse::getDY() * 0.1f;
			Math::frange(pitch, -85, 85);
		}
	}

	void Camera::calculateAngleAroundAnchor() {
		if (Mouse::isPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			angleAroundAnchor -= Mouse::getDX() * 0.3f;
			yaw = -angleAroundAnchor;
		}
	}

	void Camera::moveAnchor(float x, float y, float z) {
		anchor.x += x * std::sinf(Math::toRadians(90 + angleAroundAnchor));
		anchor.z += x * std::cosf(Math::toRadians(90 + angleAroundAnchor));

		anchor.x += z * std::sinf(Math::toRadians(angleAroundAnchor));
		anchor.z += z * std::cosf(Math::toRadians(angleAroundAnchor));

		anchor.y += y;
	}

}