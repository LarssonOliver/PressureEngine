#pragma once
#include "../Common.h"
#include "RawModel.h"

namespace Pressure {

	const class Renderer {

	public:
		void prepare() const;
		void render(const RawModel& model) const;

	};

}