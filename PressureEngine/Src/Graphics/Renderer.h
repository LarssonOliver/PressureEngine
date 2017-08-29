#pragma once
#include "../Common.h"
#include "GraphicsCommon.h"

namespace Pressure {

	const class Renderer {

	public:
		void prepare() const;
		void render(const TexturedModel& model) const;

	};

}