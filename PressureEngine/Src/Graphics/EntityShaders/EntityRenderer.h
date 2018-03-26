#pragma once
#include <unordered_map>
#include <vector>

#include "EntityShader.h"
#include "../../Math/Math.h"
#include "../Entities\Entity.h"
#include "../Models\RawModel.h"
#include "../Models\TexturedModel.h"
#include "../../Math/Geometry/ViewFrustum.h"

namespace Pressure {

	const class EntityRenderer {

	private:
		Matrix4f m_ProjectionMatrix;
		EntityShader m_Shader;
		GLFWwindow* const m_Window;

		float m_WindModifier;

	public:
		EntityRenderer(EntityShader& shader, GLFWwindow* window);
		void render(std::unordered_map<TexturedModel, std::vector<Entity>>& entities, Camera& camera);

		void updateProjectionMatrix(EntityShader& shader);
		void tick();

	private:
		void prepareTexturedModel(const TexturedModel& texturedModel);
		void unbindTexturedModel(const RawModel& model);

		void setTexParams() const;

	};

}