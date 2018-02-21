#include "PostProcessing.h"

namespace Pressure {

	const std::vector<float> PostProcessing::s_Positions = { -1, 1, -1, -1, 1, 1, 1, -1 };
	std::unique_ptr<RawModel> PostProcessing::s_Quad = nullptr;
	std::unique_ptr<ContrastChanger> PostProcessing::s_ContrastChanger = nullptr;
	std::unique_ptr<LightScatterer> PostProcessing::s_LightScatterer = nullptr;
	Window* PostProcessing::s_Window = nullptr;

	void PostProcessing::init(Window& window, Loader& loader) {
		s_Quad = std::make_unique<RawModel>(loader.loadToVao(s_Positions, 2));
		s_ContrastChanger = std::make_unique<ContrastChanger>();
		s_LightScatterer = std::make_unique<LightScatterer>(window.getWidth(), window.getHeight(), window);
		s_Window = &window;
	}

	void PostProcessing::process(unsigned int colorTexture, unsigned int lightScatterTexture) {
		start();
		s_LightScatterer->render(lightScatterTexture);
		s_ContrastChanger->render(s_LightScatterer->getResult());
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