#pragma once
#include "../Shaders/Shader.h"

namespace Pressure {

	class GuiShader : public Shader {

	private:
		int location_transformationMatrix;

	public:
		GuiShader();
		void loadTransformation(Matrix4f& matrix);
		
	protected:
		void getAllUniformLocations() override;
		void bindAttributes() override;

	};

}