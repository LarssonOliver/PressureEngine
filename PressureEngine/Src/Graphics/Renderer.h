#pragma once
#include "../Common.h"
#include "GraphicsCommon.h"
#include "Shaders\StaticShader.h"

namespace Pressure {

	const class Renderer {

	public:
		void prepare() const;
		void render(const Entity& entity, StaticShader& shader) const;

	private:
		void setTexParams() const;

	};

}