#pragma once
#include "../../Math/Vectors/Vector3f.h"
#include "ParticleTexture.h"
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API ParticleSystem {

	private:
		float ppt;
		Vector3f velocity;
		float gravityComplient;
		float lifeLength;

		ParticleTexture texture;

	public:
		ParticleSystem(ParticleTexture& texture, float pps, Vector3f& velocity, float gravityComplient, float lifeLength);
		void generateParticles(Vector3f& center);

	private:
		void emitParticle(Vector3f center, const Vector3f& spread = 0);

	};

}