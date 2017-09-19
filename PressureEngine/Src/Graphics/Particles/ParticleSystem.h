#pragma once
#include "../../Math/Math.h"

namespace Pressure {

	class ParticleSystem {

	private:
		float ppt;
		float speed;
		float gravityComplient;
		float lifeLength;

	public:
		ParticleSystem(float pps, float speed, float gravityComplient, float lifeLength);
		void generateParticles(Vector3f& center);

	private:
		void emitParticle(Vector3f& center);

	};

}