#pragma once
#include "../../Math/Math.h"

namespace Pressure {

	class Particle {

	private:
		Vector3f position;
		Vector3f speed;
		float gravityEffect;
		float lifeLength;
		float rotation;
		float scale;
		float elapsedTicks;

	public:
		Particle(Vector3f& position, Vector3f& speed, float gravityEffect, float lifeLength, float rotation, float scale);

		// Called once every tick, updates particle and returns false if particle should die.
		bool isAlive();

		Vector3f& getPosition();
		float getRotation() const;
		float getScale() const;

	};

}