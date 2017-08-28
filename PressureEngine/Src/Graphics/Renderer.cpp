#include "Renderer.h"

namespace Pressure {

	void Renderer::prepare() const {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1);
	}

	void Renderer::render(const RawModel& model) const {
		model.getVao()->bind();
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		model.getVao()->unbind();
	}

}