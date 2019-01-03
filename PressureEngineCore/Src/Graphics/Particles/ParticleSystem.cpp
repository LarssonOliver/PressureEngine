#include "ParticleSystem.h"
#include "Particle.h"
#include "../../Math/Random.h"
#include "../../Constants.h"

namespace Pressure {

	ParticleSystem::ParticleSystem(ParticleTexture& texture, float pps, Vector3f& velocity, float gravityComplient, float lifeLength)
		: m_ppt(pps), m_Velocity(velocity), m_GravityComplient(gravityComplient), m_LifeLength(lifeLength), m_Texture(texture) {
		m_ppt *= PRESSURE_TICKTIME;
	}

	void ParticleSystem::generateParticles(Vector3f& center, const Vector3f& spread) {
		Random<float> r;
		for (unsigned int i = 0; i < (unsigned int)m_ppt; i++) {
			emitParticle(center, spread);
		}
		if (r.next() < fmod(m_ppt, 1)) {
			emitParticle(center, spread);
		}
	}

	void ParticleSystem::emitParticle(Vector3f center, const Vector3f& spread) {
		Random<float> r(-1, 1);
		if (spread != 0) {
			center.x += r.next() * spread.getX();
			center.y += r.next() * spread.getY();
			center.z += r.next() * spread.getZ();
		}
		Particle(m_Texture, center, m_Velocity, m_GravityComplient, m_LifeLength + 6 * r.next(), 0, 2); 
	}

}
