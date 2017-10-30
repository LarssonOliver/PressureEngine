#include "GuiRenderer.h"
#include "../Textures/TextureManager.h"
#include <vector>

namespace Pressure {

	GuiRenderer::GuiRenderer(Loader& loader) 
		: quad(*loader.loadToVao({ -1, 1, -1, -1, 1, 1, 1, -1 }, 2)) {
	}

	GuiRenderer::~GuiRenderer() {
		shader.cleanUp();
	}

	void GuiRenderer::render(std::list<GuiTexture>& guis) {
		shader.start();
		glBindVertexArray(quad.getVaoID());
		glEnableVertexAttribArray(0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		for (auto& gui : guis) {
			glActiveTexture(GL_TEXTURE0);
			TextureManager::Inst()->BindTexture(gui.getTexture());
			shader.loadTransformation(Matrix4f().createTransformationMatrix(gui.getPosition(), gui.getScale()));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());
		}
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		glBindVertexArray(NULL);
		shader.stop();
	}

}