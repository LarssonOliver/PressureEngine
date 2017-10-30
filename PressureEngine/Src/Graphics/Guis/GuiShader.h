#pragma once
#include "../Shaders/ShaderProgram.h"

namespace Pressure {

	class GuiShader : public ShaderProgram {

	private:
		static const char* VERTEX_FILE;
		static const char* FRAGMENT_FILE;

		int location_transformationMatrix;

	public:
		GuiShader();
		void loadTransformation(Matrix4f& matrix);
		
	protected:
		void getAllUniformLocations() override;
		void bindAttributes() override;

	};

}