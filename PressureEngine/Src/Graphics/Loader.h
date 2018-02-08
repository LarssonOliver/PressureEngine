#pragma once
#include <vector>
#include <array>
#include "Models\RawModel.h"

namespace Pressure {

	class Loader {

	private:
		std::vector<VertexArray> m_VertexArrays;
		std::vector<VertexBufferLayout> m_VertexBufferLayouts;
		std::vector<IndexBuffer> m_IndexBuffers;

		// Do i even need this?
		std::vector<unsigned int> m_Textures;

	public:
		~Loader();

		RawModel loadToVao(const std::vector<float>& positions, const std::vector<float>& textureCoords, const std::vector<float>& normals, const std::vector<unsigned int>& indices);
		RawModel loadToVao(const std::vector<float>& positions, const std::vector<unsigned int>& indices);
		RawModel loadToVao(const std::vector<float>& positions, const unsigned int dimensions);
		unsigned int loadTexture(const char* filePath);
		unsigned int loadCubeMap(const char* filePath);
		
	};

}
