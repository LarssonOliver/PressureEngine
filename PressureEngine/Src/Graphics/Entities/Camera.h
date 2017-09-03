#pragma once
#include "../../Math/Math.h"

namespace Pressure {

	class Camera {

	private:
		Vector3f position;
		float pitch;
		float yaw;
		float roll;

	public:
		Camera();

		Vector3f& getPosition();
		void move(float x, float y, float z);

		float getPitch() const;
		float getYaw() const;
		float getRoll() const;

	};

}