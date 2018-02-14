#pragma once
#include <vector>
#include <list>
#include <map>
#include "../Loader.h"
#include "ParticleShader.h"
#include "Particle.h"
#include "../Models/RawModel.h"
#include "../../Math/Geometry/ViewFrustum.h"

namespace Pressure {

	class ParticleRenderer {
		
	private:
		const static std::vector<float> VERTICES;
		const static int MAX_INSTANCES;
		const static int INSTANCE_DATA_LENGTH;		

		static std::vector<float> buffer;
		int pointer;

		RawModel quad;
		ParticleShader shader;
		VertexBuffer vbo;

	public:
		ParticleRenderer(Loader& loader, Matrix4f& projectionMatrix);
		void render(std::map<ParticleTexture, std::list<Particle>>& particles, Camera& camera);
		void cleanUp();
		
	private:
		void prepare();
		void bindTexture(const ParticleTexture& texture);
		void updateViewMatrix(Vector3f& position, float rotation, float scale, Matrix4f& viewMatrix);
		void storeMatrixData(Matrix4f& matrix);
		void updateTexCoordInfo(Particle& particle);
		void finish();

	};

}