#pragma once
#include <vector>
#include <array>
#include "Models\RawModel.h"

namespace Pressure {

	class Loader {

	private:
		//std::vector<VertexArrayObject*> vaos;
		//std::vector<VertexBufferObject*> vbos;
		//std::vector<RawModel*> rawModels;

		// Do i even need this?
		std::vector<unsigned int> textures;

	public:
		~Loader();

		RawModel loadToVao(const VertexBuffer& positions, const VertexBuffer& textureCoords, const VertexBuffer& normals, const std::vector<unsigned int>& indices);
		RawModel loadToVao(const VertexBuffer& positions, const std::vector<unsigned int>& indices);
		RawModel loadToVao(const std::vector<float>& positions, const unsigned int dimensions);
		unsigned int loadTexture(const char* filePath);
		unsigned int loadCubeMap(const char* filePath);
		
	};

}
