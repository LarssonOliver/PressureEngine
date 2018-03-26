#pragma once
#include <GL\glew.h>
#include "../../Math/Math.h"
#include "ShadowShader.h"
#include <unordered_map>
#include "../Models/TexturedModel.h"
#include "../Entities/Entity.h"

namespace Pressure {

	class ShadowMapEntityRenderer {

	private:
		ShadowShader& m_Shader;
		Matrix4f& m_ProjectionViewMatrix;

	public:
		ShadowMapEntityRenderer(ShadowShader& shader, Matrix4f& projectionViewMatrix);
		void render(const std::unordered_map<TexturedModel, std::vector<Entity>>& entities);
		
	private:
		void prepareInstance(const Entity& entity);

	};

}