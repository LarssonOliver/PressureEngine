#include "ParticleMaster.h"

namespace Pressure {

	void ParticleMaster::init(Loader& loader, GLFWwindow* window) {
		renderer = ParticleRenderer(loader, Matrix4f().createProjectionMatrix(window));
	}

	void ParticleMaster::tick() {
		std::list<Particle>::iterator it = particles.begin;
		while (it != particles.end) {
			Particle& p = *it;
			if (!p.isAlive())
				particles.erase(it);
			it++;
		}
	}

	void ParticleMaster::renderParticles(Camera& camera) {
		renderer.render(particles, camera);
	}

	void ParticleMaster::cleanUp() {
		renderer.cleanUp();
	}

	void ParticleMaster::addParticle(Particle& particle) { 
		particles.emplace_back(particle);
	}

}
