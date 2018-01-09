#pragma once
#include "../Models/RawModel.h"
#include "../Loader.h"
#include "GuiTexture.h"
#include "GuiShader.h"

namespace Pressure {

	class GuiRenderer {

	private:
		const RawModel quad;
		GuiShader shader;

	public:
		GuiRenderer(Loader& loader);
		~GuiRenderer();
		void render(std::vector<GuiTexture>& guis);

	};

}