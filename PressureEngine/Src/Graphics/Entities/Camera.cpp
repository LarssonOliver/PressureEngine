#include "Camera.h"

namespace Pressure {

	Camera::Camera() 
		: position(0), pitch(0), yaw(0), roll(0)
	{ }

	Vector3f& Camera::getPosition() {
		return position;
	}

	void Camera::move(float x, float y, float z) {
		position.add(x, y, z);
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

}