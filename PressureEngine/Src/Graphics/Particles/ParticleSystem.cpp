#include "ParticleSystem.h"
#include "Particle.h"
#include "../../Math/Random.h"
#include "../../Constants.h"

namespace Pressure {

	ParticleSystem::ParticleSystem(ParticleTexture& texture, float pps, Vector3f& velocity, float gravityComplient, float lifeLength)
		: ppt(pps), velocity(velocity), gravityComplient(gravityComplient), lifeLength(lifeLength), texture(texture) {
		ppt *= PRESSURE_TICKTIME;
	}

	void ParticleSystem::generateParticles(Vector3f& center) {
		Random<float> r;
		for (unsigned int i = 0; i < (int)ppt; i++) {
			emitParticle(center);
		}
		if (r.next() < fmod(ppt, 1)) {
			emitParticle(center);
		}
	}

	void ParticleSystem::emitParticle(Vector3f center, const Vector3f& spread) {
		Random<float> r(-1, 1);
		if (spread != 0) {
			center.x += r.next() * spread.getX();
			center.y += r.next() * spread.getY();
			center.z += r.next() * spread.getZ();
		}
		Particle(texture, center, velocity, gravityComplient, lifeLength, 0, 1); 
	}

}
