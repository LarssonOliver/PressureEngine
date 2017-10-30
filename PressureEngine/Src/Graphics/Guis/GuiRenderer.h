#pragma once
#include "../Models/RawModel.h"
#include "../Loader.h"
#include <list>
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
		void render(std::list<GuiTexture>& guis);

	};

}