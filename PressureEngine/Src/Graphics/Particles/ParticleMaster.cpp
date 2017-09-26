#include "ParticleMaster.h"

namespace Pressure {

	std::map<ParticleTexture, std::list<Particle>> ParticleMaster::particles;
	std::unique_ptr<ParticleRenderer> ParticleMaster::renderer = nullptr;

	void ParticleMaster::init(Loader& loader, GLFWwindow* window) {
		renderer = std::make_unique<ParticleRenderer>(loader, Matrix4f().createProjectionMatrix(window));
	}

	void ParticleMaster::tick(Camera& camera) {
		// Creates a loop that loop through all elements in all the lists in the map.
		for (auto it = particles.begin(); it != particles.end(); it++) {
			auto& list = it->second;
			for (auto pit = list.begin(); pit != list.end(); pit++) {
				if (!pit->isAlive(camera)) {
					pit = list.erase(pit);
					if (list.size() == 0)
						particles.erase(it);
				}
			}
			// Sort the list.
		}
	}

	void ParticleMaster::renderParticles(Camera& camera) {
		renderer.get()->render(particles, camera);
	}

	void ParticleMaster::cleanUp() {
		renderer.get()->cleanUp();
	}

	void ParticleMaster::addParticle(Particle& particle) {
		// Creates new list if it does not exist, else grabs existing one.
		auto it = particles.find(particle.getTexture());
		if (it == particles.end())
			particles.emplace(particle.getTexture(), std::list<Particle>({particle}));
		else 		
			it->second.emplace_back(particle);		
	}

	void ParticleMaster::sort(std::list<Particle>& list) {

	}

}
