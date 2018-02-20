#include "PostProcessing.h"

namespace Pressure {

	const std::vector<float> PostProcessing::s_Positions = { -1, 1, -1, -1, 1, 1, 1, -1 };
	std::unique_ptr<RawModel> PostProcessing::s_Quad = nullptr;
	std::unique_ptr<ContrastChanger> PostProcessing::s_ContrastChanger = nullptr;

	void PostProcessing::init(Loader& loader) {
		s_Quad = std::make_unique<RawModel>(loader.loadToVao(s_Positions, 2));
		s_ContrastChanger = std::make_unique<ContrastChanger>();
	}

	void PostProcessing::process(unsigned int colorTexture) {
		start();
		s_ContrastChanger->render(colorTexture);
		stop();
	}

	void PostProcessing::start() {
		s_Quad->getVertexArray().bind();
		glEnableVertexAttribArray(0);
		glDisable(GL_DEPTH_TEST);
	}

	void PostProcessing::stop() {
		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		s_Quad->getVertexArray().unbind();
	}

}