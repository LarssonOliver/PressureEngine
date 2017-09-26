#pragma once
#include "../Shaders/ShaderProgram.h"

namespace Pressure {

	class ParticleShader : public ShaderProgram {

	private:
		static const char* VERTEX_FILE;
		static const char* FRAGMENT_FILE;

	public:
		ParticleShader();

	protected:
		virtual void getAllUniformLocations() override;
		virtual void bindAttributes() override;

	public:
		void loadProjectionMatrix(Matrix4f& matrix);
		void loadViewMatrix(Matrix4f& matrix);
		void loadTextureCoordInfo(Vector2f& offset1, Vector2f& offset2, float numRows, float blend);
		
	private:
		int location_projectionMatrix;
		int location_viewMatrix;
		int location_texOffset1;
		int location_texOffset2;
		int location_texCoordInfo;

	};

}