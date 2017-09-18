#include "WaterRenderer.h"
#include <iostream>

namespace Pressure {

	WaterRenderer::WaterRenderer(GLFWwindow* window, WaterFrameBuffers& fbos) : window(window), fbos(fbos)  {
		shader.start();
		shader.connectTextureUnits();
		updateProjectionmatrix();
	}

	void WaterRenderer::updateProjectionmatrix() {
		shader.start();
		shader.loadProjectionMatrix(Matrix4f().createProjectionMatrix(window));
		shader.stop();
	}

	void WaterRenderer::tick() {
		waveModifier += 0.3f;
		//std::cout << waveModifier << std::endl;
		if (waveModifier > 360)
			waveModifier -= 360;
	}

	void WaterRenderer::render(std::vector<Water>& water, Light& sun, Camera& camera) {
		prepare(water, sun, camera);
		for (Water& w : water) {
			shader.loadTransformationMatrix(Matrix4f().createTransformationMatrix(w.getPosition(), Vector3f(0), 1));
			glDrawElements(GL_TRIANGLES, w.getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		finish(water);
	}

	void WaterRenderer::prepare(std::vector<Water>& water, Light& sun, Camera& camera) {
		shader.start();
		shader.loadViewMatrix(camera);
		shader.loadWaveModifier(Math::toRadians(waveModifier));
		shader.loadLight(sun);
		water[0].getModel()->getVao()->bind();
		glEnableVertexAttribArray(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fbos.getReflectionTexture());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, fbos.getRefractionTexture());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, fbos.getRefractionDepthTexture());
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void WaterRenderer::finish(std::vector<Water>& water) {
		glDisableVertexAttribArray(0);
		water[0].getModel()->getVao()->unbind();
		shader.stop();
		glDisable(GL_BLEND);
	}

}