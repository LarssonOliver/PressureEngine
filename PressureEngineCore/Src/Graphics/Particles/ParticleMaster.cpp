#include "ParticleMaster.h"

namespace Pressure {

	std::map<ParticleTexture, std::list<Particle>> ParticleMaster::s_Particles;
	std::unique_ptr<ParticleRenderer> ParticleMaster::s_Renderer = nullptr;

	void ParticleMaster::init(Loader& loader, GLFWwindow* window) {
		s_Renderer = std::make_unique<ParticleRenderer>(loader, Matrix4f().createProjectionMatrix(window));
	}

	void ParticleMaster::tick(Camera& camera) {
		// Creates a loop that loop through all elements in all the lists in the map.
		auto map = s_Particles.begin();
		while (map != s_Particles.end()) {
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
				map = s_Particles.erase(map);
			else map++;
		}

	}

	void ParticleMaster::renderParticles(Camera& camera) {
		s_Renderer.get()->render(s_Particles, camera);
	}

	void ParticleMaster::cleanUp() {
		s_Renderer.get()->cleanUp();
	}

	void ParticleMaster::addParticle(Particle& particle) {
		// Creates new list if it does not exist, else grabs existing one.
		auto it = s_Particles.find(particle.getTexture());
		if (it == s_Particles.end())
			s_Particles.emplace(particle.getTexture(), std::list<Particle>({ particle }));
		else
			it->second.emplace_front(particle);
	}

	void ParticleMaster::updateProjectionMatrix(Window& window) {
		s_Renderer->updateProjectionMatrix(window);
	}

	bool ParticleMaster::sort_particles(const Particle& left, const Particle& right) {
		return left.getDistance() > right.getDistance();
	}

}
