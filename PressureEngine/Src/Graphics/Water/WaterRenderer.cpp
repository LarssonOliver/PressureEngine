#include "WaterRenderer.h"

namespace Pressure {

	WaterRenderer::WaterRenderer(GLFWwindow* window) : window(window), waveModifier(0) {
		updateProjectionmatrix();
	}

	void WaterRenderer::updateProjectionmatrix() {
		shader.start();
		shader.loadProjectionMatrix(Matrix4f().createProjectionMatrix(window));
		shader.stop();
	}

	void WaterRenderer::tick() {
		waveModifier++;
		if (waveModifier > 360)
			waveModifier -= 360;
	}

	void WaterRenderer::render(std::vector<Water>& water, Camera& camera) {
		shader.start();
		shader.loadViewMatrix(camera);
		shader.loadWaveModifier(Math::toRadians(waveModifier));
		water[0].getModel()->getVao()->bind();
		glEnableVertexAttribArray(0);
		for (Water& w : water) {
			shader.loadTransformationMatrix(Matrix4f().createTransformationMatrix(w.getPosition(), Vector3f(0), 1));
			glDrawElements(GL_TRIANGLES, w.getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		glDisableVertexAttribArray(0);
		water[0].getModel()->getVao()->unbind();
		shader.stop();
	}

}