#include "PostProcessing.h"
#include "../../Services/Properties.h"

namespace Pressure {

	const std::vector<float> PostProcessing::s_Positions = { -1, 1, -1, -1, 1, 1, 1, -1 };
	std::unique_ptr<RawModel> PostProcessing::s_Quad = nullptr;
	std::unique_ptr<ContrastChanger> PostProcessing::s_ContrastChanger = nullptr;
	std::unique_ptr<LightScatterer> PostProcessing::s_LightScatterer = nullptr;
	std::unique_ptr<DepthOfField> PostProcessing::s_DepthOfField = nullptr;
	Window* PostProcessing::s_Window = nullptr;
	Camera* PostProcessing::s_Camera = nullptr;

	void PostProcessing::init(Window& window, Camera& camera, Loader& loader) {
		s_Quad = std::make_unique<RawModel>(loader.loadToVao(s_Positions, 2));
		s_ContrastChanger = std::make_unique<ContrastChanger>();
		s_LightScatterer = std::make_unique<LightScatterer>(window.getWidth(), window.getHeight(), window);		
		s_DepthOfField = std::make_unique<DepthOfField>(window.getWidth(), window.getHeight(), window);
		s_Window = &window;
		s_Camera = &camera;
	}

	void PostProcessing::process(FrameBuffer& frameBuffer, unsigned int lightScatterTexture, Vector3f& lightPosition) {
		start();
		s_LightScatterer->render(frameBuffer.getColorTexture(), lightScatterTexture, lightPosition, *s_Camera);
		if (Properties::get("useDepthOfField") == "1") {
			s_DepthOfField->render(s_LightScatterer->getResult(), frameBuffer.getDepthTexture());
			s_ContrastChanger->render(s_DepthOfField->getResult());
		} else
			s_ContrastChanger->render(s_LightScatterer->getResult());
		stop();
	}

	void PostProcessing::updateProjectionMatrix() {
		s_LightScatterer = std::make_unique<LightScatterer>(s_Window->getWidth(), s_Window->getHeight(), *s_Window);
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