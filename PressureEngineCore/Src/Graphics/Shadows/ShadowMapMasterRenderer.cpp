#include "ShadowMapMasterRenderer.h"

namespace Pressure {

	const int ShadowMapMasterRenderer::SHADOW_MAP_SIZE = 8192; // Change in frag shader if changed here.

	ShadowMapMasterRenderer::ShadowMapMasterRenderer(Camera& camera, Window& window)
		: m_ShadowFbo(window, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, 1, 1, FrameBuffer::DepthBufferType::TEXTURE), m_ShadowBox(m_LightViewMatrix, camera, window), m_EntityRenderer(m_Shader, m_ProjectionViewMatrix) {
		//: shadowFbo(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, window), shadowBox(lightViewMatrix, camera, window), entityRenderer(shader, projectionViewMatrix) {
		createOffset();
	}

	ShadowMapMasterRenderer::~ShadowMapMasterRenderer() {
		m_Shader.cleanUp();
	}

	void ShadowMapMasterRenderer::render(std::unordered_map<TexturedModel, std::vector<Entity>>& entities, Light& sun) {
		m_ShadowBox.tick();
		prepare(sun.getPosition().negate(Vector3f()), m_ShadowBox);
		m_EntityRenderer.render(entities);
		finish();
	}

	Matrix4f ShadowMapMasterRenderer::getToShadowMapSpaceMatrix() {
		return m_Offset.mul(m_ProjectionViewMatrix, Matrix4f());
	}

	unsigned int ShadowMapMasterRenderer::getShadowMap() {
		return m_ShadowFbo.getDepthTexture();
		//return shadowFbo.getShadowMap();
	}

	float ShadowMapMasterRenderer::getShadowDistance() const {
		return m_ShadowBox.getShadowDistance();
	}

	void ShadowMapMasterRenderer::setShadowDistance(float shadowDistance) {
		m_ShadowBox.setShadowDistance(shadowDistance);
	}

	Matrix4f& ShadowMapMasterRenderer::getLightSpaceTransform() {
		return m_LightViewMatrix;
	}

	void ShadowMapMasterRenderer::prepare(Vector3f& lightDirection, ShadowBox& box) {
		updateOrthoProjectionMatrix(box.getWidth(), box.getHeight(), box.getLength());
		updateLightViewMatrix(lightDirection, box.getCenter());
		m_ProjectionMatrix.mul(m_LightViewMatrix, m_ProjectionViewMatrix);
		m_ShadowFbo.bind();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
		m_Shader.start();
	}

	void ShadowMapMasterRenderer::finish() {
		m_Shader.stop();
		m_ShadowFbo.unbind();
	}

	void ShadowMapMasterRenderer::updateLightViewMatrix(Vector3f& direction, Vector3f& center) {		
		direction.normalize();
		center.negate();
		m_LightViewMatrix.identity();
 		float pitch = std::acosf(Vector2f(direction.getX(), direction.getZ()).length());
		m_LightViewMatrix.rotate(pitch, Vector3f(1, 0, 0));
		float yaw = std::atanf(direction.getX() / direction.getZ());
		yaw = direction.getZ() > 0 ? yaw - (float)std::_Pi : yaw;
		m_LightViewMatrix.rotate(-yaw, Vector3f(0, 1, 0));
		m_LightViewMatrix.translate(center);
	}

	void ShadowMapMasterRenderer::updateOrthoProjectionMatrix(float width, float height, float length) {
		m_ProjectionMatrix.identity();
		m_ProjectionMatrix.set(0, 0, 2.f / width);
		m_ProjectionMatrix.set(1, 1, 2.f / height);
		m_ProjectionMatrix.set(2, 2, -2.f / length);
	}

	void ShadowMapMasterRenderer::createOffset() {
		m_Offset.translate(Vector3f(0.5f));
		m_Offset.scale(0.5f);
	}

}
