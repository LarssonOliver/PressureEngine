#include "ParticleMaster.h"

namespace Pressure {

	std::map<ParticleTexture, std::list<Particle>> ParticleMaster::particles;
	std::unique_ptr<ParticleRenderer> ParticleMaster::renderer = nullptr;

	void ParticleMaster::init(Loader& loader, GLFWwindow* window) {
		renderer = std::make_unique<ParticleRenderer>(loader, Matrix4f().createProjectionMatrix(window));
	}

	void ParticleMaster::tick(Camera& camera) {
		// Creates a loop that loop through all elements in all the lists in the map.
		auto map = particles.begin();
		while (map != particles.end()) {
			bool empty = false;
			auto& list = map->second;
			auto particle = list.begin();
			while (particle != list.end()) {
				if (!particle->isAlive(camera)) {
					particle = list.erase(particle);
					empty = list.size() == 0;
				}
				else
					particle++;
			}

			if (!map->first.isUseAdditiveBlending())
				list.sort(sort_particles);

			if (empty)
				map = particles.erase(map);
			else map++;
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
			particles.emplace(particle.getTexture(), std::list<Particle>({ particle }));
		else
			it->second.emplace_front(particle);
	}

	bool ParticleMaster::sort_particles(const Particle& left, const Particle& right) {
		return left.getDistance() > right.getDistance();
	}

}
