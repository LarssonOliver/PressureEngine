#pragma once
#include "../../Math/Math.h"

namespace Pressure {

	class Camera {

	private:
		// Cameras position.
		Vector3f position;
		// Cameras rotational values.
		float pitch;
		float yaw;
		float roll;

		// Camera anchor variables.
		// The point the camera moves around.
		Vector3f anchor;
		float distanceFromAnchor;
		float angleAroundAnchor;

		// Movement Variables.
		// Cameras movement speed.
		float speed;
		//TODO: Implement smooth starts and stops to movement.
		//float acceleration;

	public:
		Camera();

		Vector3f& getPosition();
		Vector3f& getAnchor();
		void tick();

		float getPitch() const;
		float getYaw() const;
		float getRoll() const;

		void setSpeed(const float speed);
		float getSpeed() const;

	private: 
		float calculateHorizontalDistance();
		float calculateVerticalDistance();
		void calculateCameraPosition();

		void calculateZoom();
		void calculatePitch();
		void calculateAngleAroundAnchor();

		// Moves the anchor relative to the camera, not the world.
		void moveAnchor(float x, float y, float z);

	};

}