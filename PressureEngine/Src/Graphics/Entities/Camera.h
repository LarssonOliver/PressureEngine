#pragma once
#include "../../Math/Vectors/Vector3f.h"

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
		float max_speed;
		Vector3f speed;
		Vector3f acceleration;

	public:
		Camera();

		Vector3f& getPosition();
		Vector3f& getAnchor();
		void tick();

		float getPitch() const;
		float getYaw() const;
		float getRoll() const;
		void invertPitch(); // Used when rendering reflection textures.

		void setSpeed(const float speed);
		float getSpeed() const;

		float getDistanceFromAnchor() const;

	private: 
		float calculateHorizontalDistance();
		float calculateVerticalDistance();
		void calculateCameraPosition();

		void calculateZoom();
		void calculatePitch();
		void calculateAngleAroundAnchor();

		// Moves the anchor relative to the camera, not the world.
		void moveAnchor(const Vector3f& speed);

	};

}