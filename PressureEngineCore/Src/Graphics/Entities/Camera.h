#pragma once
#include "../../Math/Vectors/Vector3f.h"

namespace Pressure {

	class Camera {

	private:
		// Cameras position.
		Vector3f m_Position;
		// Cameras rotational values.
		float m_Pitch;
		float m_Yaw;
		float m_Roll;

		// Camera anchor variables.
		// The point the camera moves around.
		Vector3f m_Anchor;
		float m_DistanceFromAnchor;
		float m_AngleAroundAnchor;

		// Movement Variables.
		// Cameras movement speed.
		float m_MaxSpeed;
		Vector3f m_Speed;
		Vector3f m_Acceleration;

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