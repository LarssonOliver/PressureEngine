#include "GuiRenderer.h"
#include "../Textures/TextureManager.h"
#include <vector>

namespace Pressure {

	GuiRenderer::GuiRenderer(Loader& loader) 
		: m_Quad(loader.loadToVao({ -1, 1, -1, -1, 1, 1, 1, -1 }, 2)) {
	}

	GuiRenderer::~GuiRenderer() {
		m_Shader.cleanUp();
	}

	void GuiRenderer::render(std::vector<GuiTexture>& guis) {
		m_Shader.start();
		m_Quad.getVertexArray().bind();
		glEnableVertexAttribArray(0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		for (auto& gui : guis) {
			glActiveTexture(GL_TEXTURE0);
			if(gui.isTextureManaged())
				TextureManager::Inst()->BindTexture(gui.getTexture());
			else 
				glBindTexture(GL_TEXTURE_2D, gui.getTexture());
			m_Shader.loadTransformation(Matrix4f().createTransformationMatrix(gui.getPosition(), gui.getScale()));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Quad.getVertexCount());
		}
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		m_Quad.getVertexArray().unbind();
		m_Shader.stop();
	}

}