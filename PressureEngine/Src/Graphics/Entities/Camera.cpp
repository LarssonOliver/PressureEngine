#include "Camera.h"
#include <cmath>
#include "../../Input/Input.h"
#include "../../Math/Math.h"

namespace Pressure {

	Camera::Camera()
		: position(0), pitch(0), yaw(0), roll(0), anchor(0), distanceFromAnchor(5),
		angleAroundAnchor(0), max_speed(0.5f), speed(0), acceleration(0)
	{ }

	Vector3f& Camera::getPosition() {
		return position;
	}

	Vector3f& Camera::getAnchor() {
		return anchor;
	}

	void Camera::tick() {

		static const float acc = 0.05f;

		if (Keyboard::isPressed(GLFW_KEY_W))
			acceleration.setZ(-acc);
		else if (Keyboard::isPressed(GLFW_KEY_S))
			acceleration.setZ(acc);
		else {
			acceleration.z = 0;
			speed.z = 0;
		} if (Keyboard::isPressed(GLFW_KEY_W) && Keyboard::isPressed(GLFW_KEY_S))
			acceleration.setZ(0);
		//if (acceleration.z > 0 - acc && acceleration.z < 0 + acc)
		//	acceleration.setZ(0);

		if (Keyboard::isPressed(GLFW_KEY_A))
			acceleration.setX(-acc);
		else if (Keyboard::isPressed(GLFW_KEY_D))
			acceleration.setX(acc);
		else {
			acceleration.x = 0;
			speed.x = 0;
		} if (Keyboard::isPressed(GLFW_KEY_A) && Keyboard::isPressed(GLFW_KEY_D))
			acceleration.setX(0);
		//if (acceleration.x > 0 - acc && acceleration.x < 0 + acc)
		//	acceleration.setX(0);

		speed.add(acceleration);
		Math::frange(speed.x, -max_speed, max_speed);
		//Math::frange(speed.y, -max_speed, max_speed);
		Math::frange(speed.z, -max_speed, max_speed);
		moveAnchor(speed);

		calculateZoom();
		calculatePitch();
		calculateAngleAroundAnchor();
		calculateCameraPosition();
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
		this->max_speed = speed;
	}

	float Camera::getSpeed() const {
		return max_speed;
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
		position.x = anchor.x + horizontalDistance * std::sinf(Math::toRadians(angleAroundAnchor));
		position.z = anchor.z + horizontalDistance * std::cosf(Math::toRadians(angleAroundAnchor));
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

			// Makes sure that the angle always is 0 >= x >= 360
			if (angleAroundAnchor > 360)
				angleAroundAnchor -= 360;
			else if (angleAroundAnchor < 0)
				angleAroundAnchor += 360;

			yaw = -angleAroundAnchor;
		}
	}

	void Camera::moveAnchor(const Vector3f& speed) {
		anchor.x += speed.x * std::sinf(Math::toRadians(90 + angleAroundAnchor));
		anchor.z += speed.x * std::cosf(Math::toRadians(90 + angleAroundAnchor));

		anchor.x += speed.z * std::sinf(Math::toRadians(angleAroundAnchor));
		anchor.z += speed.z * std::cosf(Math::toRadians(angleAroundAnchor));

		anchor.y += speed.y;
	}

}