#pragma once
#include "../Common.h"
#include "GraphicsCommon.h"
#include "Shaders\StaticShader.h"

namespace Pressure {

	const class Renderer {

	private:
		Matrix4f projectionMatrix;

	public:
		Renderer(StaticShader& shader);
		void prepare() const;
		void render(const Entity& entity, StaticShader& shader) const;

	private:
		void setTexParams() const;

	};

}