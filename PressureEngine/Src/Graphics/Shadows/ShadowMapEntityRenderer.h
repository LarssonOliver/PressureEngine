#pragma once
#include <GL\glew.h>
#include "../../Math/Math.h"
#include "ShadowShader.h"
#include <map>
#include "../Models/TexturedModel.h"
#include "../Entities/Entity.h"

namespace Pressure {

	class ShadowMapEntityRenderer {

	private:
		ShadowShader& shader;
		Matrix4f& projectionViewMatrix;

	public:
		ShadowMapEntityRenderer(ShadowShader& shader, Matrix4f& projectionViewMatrix);
		void render(const std::map<TexturedModel, std::vector<Entity>>& entities);
		
	private:
		void bindModel(const RawModel& rawModel) const;
		void prepareInstance(const Entity& entity);

	};

}