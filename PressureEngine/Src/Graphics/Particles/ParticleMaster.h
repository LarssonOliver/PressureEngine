#pragma once
#include <list>
#include "Particle.h"
#include "ParticleRenderer.h"

namespace Pressure {

	class ParticleMaster {

	private:
		static std::list<Particle> particles;
		static ParticleRenderer renderer;

	public:
		static void init(Loader& loader, GLFWwindow* window);
		static void tick();

		static void renderParticles(Camera& camera);
		static void cleanUp();

		static void addParticle(Particle& particle);

	};

}