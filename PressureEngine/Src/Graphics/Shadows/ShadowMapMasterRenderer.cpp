#include "ShadowMapMasterRenderer.h"

namespace Pressure {

	const int ShadowMapMasterRenderer::SHADOW_MAP_SIZE = 8192; // Change in frag shader if changed here.

	ShadowMapMasterRenderer::ShadowMapMasterRenderer(Camera& camera, Window& window)
		: shadowFbo(window, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, DepthBufferType::TEXTURE), shadowBox(lightViewMatrix, camera, window), entityRenderer(shader, projectionViewMatrix) {
		//: shadowFbo(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, window), shadowBox(lightViewMatrix, camera, window), entityRenderer(shader, projectionViewMatrix) {
		createOffset();
	}

	ShadowMapMasterRenderer::~ShadowMapMasterRenderer() {
		shader.cleanUp();
	}

	void ShadowMapMasterRenderer::render(std::map<TexturedModel, std::vector<Entity>>& entities, Light& sun) {
		shadowBox.tick();
		prepare(sun.getPosition().negate(Vector3f()), shadowBox);
		entityRenderer.render(entities);
		finish();
	}

	Matrix4f ShadowMapMasterRenderer::getToShadowMapSpaceMatrix() {
		return offset.mul(projectionViewMatrix, Matrix4f());
	}

	unsigned int ShadowMapMasterRenderer::getShadowMap() {
		return shadowFbo.getDepthTexture();
		//return shadowFbo.getShadowMap();
	}

	Matrix4f& ShadowMapMasterRenderer::getLightSpaceTransform() {
		return lightViewMatrix;
	}

	void ShadowMapMasterRenderer::prepare(Vector3f& lightDirection, ShadowBox& box) {
		updateOrthoProjectionMatrix(box.getWidth(), box.getHeight(), box.getLength());
		updateLightViewMatrix(lightDirection, box.getCenter());
		projectionMatrix.mul(lightViewMatrix, projectionViewMatrix);
		shadowFbo.bind();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
		shader.start();
	}

	void ShadowMapMasterRenderer::finish() {
		shader.stop();
		shadowFbo.unbind();
	}

	void ShadowMapMasterRenderer::updateLightViewMatrix(Vector3f& direction, Vector3f& center) {		
		direction.normalize();
		center.negate();
		lightViewMatrix.identity();
 		float pitch = std::acosf(Vector2f(direction.getX(), direction.getZ()).length());
		lightViewMatrix.rotate(pitch, Vector3f(1, 0, 0));
		float yaw = std::atanf(direction.getX() / direction.getZ());
		yaw = direction.getZ() > 0 ? yaw - (float)std::_Pi : yaw;
		lightViewMatrix.rotate(-yaw, Vector3f(0, 1, 0));
		lightViewMatrix.translate(center);
	}

	void ShadowMapMasterRenderer::updateOrthoProjectionMatrix(float width, float height, float length) {
		projectionMatrix.identity();
		projectionMatrix.set(0, 0, 2.f / width);
		projectionMatrix.set(1, 1, 2.f / height);
		projectionMatrix.set(2, 2, -2.f / length);
	}

	void ShadowMapMasterRenderer::createOffset() {
		offset.translate(Vector3f(0.5f));
		offset.scale(0.5f);
	}

}
