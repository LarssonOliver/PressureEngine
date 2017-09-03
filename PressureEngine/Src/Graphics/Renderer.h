#pragma once
#include "../Common.h"
#include "GraphicsCommon.h"
#include "Shaders\StaticShader.h"

namespace Pressure {

	const class Renderer {

	private:
		Matrix4f projectionMatrix;

	public:
		Renderer(StaticShader& shader, GLFWwindow* window);
		void prepare() const;
		void render(const Entity& entity, StaticShader& shader) const;

		void updateProjectionMatrix(StaticShader& shader, GLFWwindow* window);

	private:
		void setTexParams() const;

	};

}