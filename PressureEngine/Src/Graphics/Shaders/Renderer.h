#pragma once
#include <map>
#include <vector>

#include "EntityShader.h"
#include "../../Math/Math.h"
#include "../Entities\Entity.h"
#include "../Models\RawModel.h"
#include "../Models\TexturedModel.h"

namespace Pressure {

	const class Renderer {

	private:
		Matrix4f projectionMatrix;
		EntityShader shader;
		GLFWwindow* const window;

	public:
		Renderer(EntityShader& shader, GLFWwindow* window);
		void render(std::map<TexturedModel, std::vector<Entity>>& entities, Matrix4f& toShadowSpace);

		void updateProjectionMatrix(EntityShader& shader);

	private:
		void prepareTexturedModel(const TexturedModel& texturedModel);
		void unbindTexturedModel(const RawModel& model);
		void prepareInstance(Entity& entity);

		void setTexParams() const;

	};

}