#pragma once
#include "ShadowFrameBuffer.h"
#include "ShadowShader.h"
#include "ShadowBox.h"
#include "ShadowMapEntityRenderer.h"
#include "../Entities/Light.h"

namespace Pressure {

	class ShadowMapMasterRenderer {

	private:
		static const int SHADOW_MAP_SIZE;

		ShadowFrameBuffer shadowFbo;
		ShadowShader shader;
		ShadowBox shadowBox;
		Matrix4f projectionMatrix;
		Matrix4f lightViewMatrix;
		Matrix4f projectionViewMatrix;
		Matrix4f offset;

		ShadowMapEntityRenderer entityRenderer;

	public:
		ShadowMapMasterRenderer(Camera& camera, Window& window);
		~ShadowMapMasterRenderer();
		void render(std::map<TexturedModel, std::vector<Entity>>& entities, Light& sun);
		
		Matrix4f getToShadowMapSpaceMatrix();
		unsigned int getShadowMap();
		Matrix4f& getLightSpaceTransform();

	private:
		void prepare(Vector3f& lightDirection, ShadowBox& box);
		void finish();
		void updateLightViewMatrix(Vector3f& direction, Vector3f center);
		void updateOrthoProjectionMatrix(float width, float height, float length);
		void createOffset();

	};

}