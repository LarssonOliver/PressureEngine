#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleShader.h"
#include "../Loader.h"
#include "../Models/RawModel.h"

namespace Pressure {

	class ParticleRenderer {
		
	private:
		const static std::vector<float> VERTICES;
		
		RawModel* quad;
		ParticleShader shader;

	public:
		ParticleRenderer(Loader& loader, Matrix4f& projectionMatrix);
		void render(std::list<Particle>& particles, Camera& camera);
		void cleanUp();
		
	private:
		void prepare();
		void updateViewMatrix(Vector3f& position, float rotation, float scale, Matrix4f& viewMatrix);
		void finish();

	};

}