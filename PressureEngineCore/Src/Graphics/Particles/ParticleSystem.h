#pragma once
#include "../../Math/Vectors/Vector3f.h"
#include "ParticleTexture.h"
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API ParticleSystem {

	private:
		float m_ppt;
		Vector3f m_Velocity;
		float m_GravityComplient;
		float m_LifeLength;

		ParticleTexture m_Texture;

	public:
		ParticleSystem(ParticleTexture& texture, float pps, Vector3f& velocity, float gravityComplient, float lifeLength);
		void generateParticles(Vector3f& center, const Vector3f& spread = 0);

	private:
		void emitParticle(Vector3f center, const Vector3f& spread);

	};

}