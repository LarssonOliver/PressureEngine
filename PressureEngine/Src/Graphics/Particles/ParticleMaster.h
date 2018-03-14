#pragma once
#include <list>
#include <memory>
#include <map>
#include "ParticleTexture.h"
#include "ParticleRenderer.h"
#include "Particle.h"

namespace Pressure {

	class ParticleMaster {

	private:
		static std::map<ParticleTexture, std::list<Particle>> s_Particles;
		static std::unique_ptr<ParticleRenderer> s_Renderer;

	public:
		static void init(Loader& loader, GLFWwindow* window);
		static void tick(Camera& camera);

		static void renderParticles(Camera& camera);
		static void cleanUp();

		static void addParticle(Particle& particle);

		static void updateProjectionMatrix(Window& window);

	private:
		ParticleMaster() = delete;

		static bool sort_particles(const Particle& left, const Particle& right);

	};

}