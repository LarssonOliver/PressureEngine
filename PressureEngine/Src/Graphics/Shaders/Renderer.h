#pragma once
#include <map>
#include <vector>

#include "EntityShader.h"
#include "../../Math/Math.h"
#include "../Entities\Entity.h"
#include "../Models\RawModel.h"
#include "../Models\TexturedModel.h"
#include "../../Math/Geometry/ViewFrustum.h"

namespace Pressure {

	const class Renderer {

	private:
		Matrix4f projectionMatrix;
		EntityShader shader;
		GLFWwindow* const window;
		ViewFrustum frustum;

		float windModifier;

	public:
		Renderer(EntityShader& shader, GLFWwindow* window);
		void render(std::map<TexturedModel, std::vector<Entity>>& entities, Camera& camera);

		void updateProjectionMatrix(EntityShader& shader);
		void tick();

	private:
		void prepareTexturedModel(const TexturedModel& texturedModel);
		void unbindTexturedModel(const RawModel& model);

		void setTexParams() const;

	};

}