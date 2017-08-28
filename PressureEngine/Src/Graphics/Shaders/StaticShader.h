#pragma once
#include "ShaderProgram.h"

namespace Pressure {

	class StaticShader : public ShaderProgram {

#define PRESSURE_ENGINE_STATIC_VERTEX_FILE "Src/Graphics/Shaders/VertexShader.glsl"
#define PRESSURE_ENGINE_STATIC_FRAGMENT_FILE "Src/Graphics/Shaders/FragmentShader.glsl"

	public:
		StaticShader();

	protected:
		virtual void bindAttributes() override;

	};

}
