#pragma once

#include "../ImageRenderer.h"
#include "LightScatteringShader.h"
#include "../../Entities/Camera.h"

namespace Pressure {

	class LightScatterer {

	private:
		Window& m_Window;

		ImageRenderer m_Renderer;
		LightScatteringShader m_Shader;
		Matrix4f m_ProjectionMatrix;
		Matrix4f m_ProjectionViewMatrix;

	public:
		LightScatterer(unsigned int targetWidth, unsigned int targetHeight, Window& window);
		void render(unsigned int colorTexture, unsigned int lightTexture, Vector3f& lightPosition, Camera& camera);
		unsigned int getResult();

		void updateProjectionMatrix();

	};

}