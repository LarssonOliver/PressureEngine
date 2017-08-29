#include "Renderer.h"

namespace Pressure {

	void Renderer::prepare() const {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1);
	}

	void Renderer::render(const TexturedModel& texturedModel) const {
		RawModel& model = *texturedModel.getRawModel();
		model.getVao()->bind();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glActiveTexture(GL_TEXTURE0);
		TextureManager::Inst()->BindTexture(texturedModel.getTexture()->getID());
		glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0); 
		glDisableVertexAttribArray(1);
		model.getVao()->unbind();
	}

}