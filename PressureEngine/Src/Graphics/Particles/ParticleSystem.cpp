#include "../../Math/Math.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "../../Constants.h"

namespace Pressure {

	ParticleSystem::ParticleSystem(float pps, float speed, float gravityComplient, float lifeLength) 
		: ppt(pps), speed(speed), gravityComplient(gravityComplient), lifeLength(lifeLength) {
		ppt *= PRESSURE_TICKTIME;
	}

	void ParticleSystem::generateParticles(Vector3f& center) {
		Random<float> r;
		for (int i = 0; i < (int)ppt; i++) {
			emitParticle(center);
		}
		if (r.next() < fmod(ppt, 1));
	}

	void ParticleSystem::emitParticle(Vector3f& center) {
		Random<float> r(-1, 1);
		Vector3f vel(r.next(), 1, r.next());
		vel.normalize();
		vel.scale(speed);
		Particle(Vector3f(center), vel, gravityComplient, lifeLength, 0, 1);
	}

}
