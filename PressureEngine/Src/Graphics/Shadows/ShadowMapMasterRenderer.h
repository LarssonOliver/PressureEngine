#pragma once
#include <unordered_map>
#include "../GLObjects/FrameBuffer.h"
#include "ShadowShader.h"
#include "ShadowBox.h"
#include "ShadowMapEntityRenderer.h"
#include "../Entities/Light.h"

namespace Pressure {

	class ShadowMapMasterRenderer {

	private:
		static const int SHADOW_MAP_SIZE;

		FrameBuffer m_ShadowFbo;
		ShadowShader m_Shader;
		ShadowBox m_ShadowBox;
		Matrix4f m_ProjectionMatrix;
		Matrix4f m_LightViewMatrix;
		Matrix4f m_ProjectionViewMatrix;
		Matrix4f m_Offset;

		ShadowMapEntityRenderer m_EntityRenderer;

	public:
		ShadowMapMasterRenderer(Camera& camera, Window& window);
		~ShadowMapMasterRenderer();
		void render(std::unordered_map<TexturedModel, std::vector<Entity>>& entities, Light& sun);
		
		Matrix4f getToShadowMapSpaceMatrix();
		unsigned int getShadowMap();
		float getShadowDistance() const;
		void setShadowDistance(float shadowDistance);
		Matrix4f& getLightSpaceTransform();

	private:
		void prepare(Vector3f& lightDirection, ShadowBox& box);
		void finish();
		void updateLightViewMatrix(Vector3f& direction, Vector3f& center);
		void updateOrthoProjectionMatrix(float width, float height, float length);
		void createOffset();

	};

}