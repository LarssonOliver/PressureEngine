#include "ParticleMaster.h"

namespace Pressure {

	std::list<Particle> ParticleMaster::particles;
	std::unique_ptr<ParticleRenderer> ParticleMaster::renderer = nullptr;

	void ParticleMaster::init(Loader& loader, GLFWwindow* window) {
		renderer = std::make_unique<ParticleRenderer>(loader, Matrix4f().createProjectionMatrix(window));
	}

	void ParticleMaster::tick() {
		std::list<Particle>::iterator it = particles.begin();
		while (it != particles.end()) {
			if (!(*it).isAlive())
				it = particles.erase(it);
			else
				it++;
		}
	}

	void ParticleMaster::renderParticles(Camera& camera) {
		renderer.get()->render(particles, camera);
	}

	void ParticleMaster::cleanUp() {
		renderer.get()->cleanUp();
	}

	void ParticleMaster::addParticle(Particle& particle) { 
		particles.push_back(particle);
	}

}
