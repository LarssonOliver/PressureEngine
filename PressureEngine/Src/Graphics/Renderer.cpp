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
		setTexParams();
		glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0); 
		glDisableVertexAttribArray(1);
		model.getVao()->unbind();
	}

	void Renderer::setTexParams() const {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

}