#include "../../Constants.h"
#include "Particle.h"
#include "ParticleMaster.h"

namespace Pressure {

	Particle::Particle(Vector3f& position, Vector3f& speed, float gravityEffect, float lifeLength, float rotation, float scale)
		: position(position), speed(speed), gravityEffect(gravityEffect), lifeLength(lifeLength), rotation(rotation), scale(scale), elapsedTicks(0) {	
		ParticleMaster::addParticle(*this);
	}

	bool Particle::isAlive() {
		speed.y -= PRESSURE_GRAVITY * gravityEffect * elapsedTicks * PRESSURE_TICKTIME;
		position.add(speed);
		elapsedTicks++;
		return elapsedTicks < lifeLength;
	}

	Vector3f& Particle::getPosition() {
		return position;
	}

	float Particle::getRotation() const {
		return rotation;
	}

	float Particle::getScale() const {
		return scale;
	}

}
