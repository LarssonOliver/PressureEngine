#pragma once
#include <map>
#include <vector>

#include "Shaders\StaticShader.h"
#include "../Math/Math.h"
#include "Entities\Entity.h"
#include "Models\RawModel.h"
#include "Models\TexturedModel.h"

namespace Pressure {

	const class Renderer {

	private:
		Matrix4f projectionMatrix;
		StaticShader shader;
		GLFWwindow* const window;

	public:
		Renderer(StaticShader& shader, GLFWwindow* window);
		void prepare() const;
		void render(std::map<TexturedModel, std::vector<Entity>>& entities);

		void updateProjectionMatrix(StaticShader& shader);

	private:
		void prepareTexturedModel(const TexturedModel& texturedModel);
		void unbindTexturedModel(const RawModel& model);
		void prepareInstance(Entity& entity);

		void setTexParams() const;

	};

}