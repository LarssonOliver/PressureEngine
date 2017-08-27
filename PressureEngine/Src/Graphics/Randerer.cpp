#include "Randerer.h"

namespace Pressure {

	void Renderer::prepare() const {
		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::render(const RawModel& model) const {
		glBindVertexArray(model.getVaoID());
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}

}