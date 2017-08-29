#pragma once
#include "../Common.h"
#include "GraphicsCommon.h"

namespace Pressure {

	class Loader {

	private:
		std::vector<VertexArrayObject*> vaos;
		std::vector<VertexBufferObject*> vbos;
		std::vector<RawModel*> rawModels;

		// Do i even need this?
		std::vector<unsigned int> textures;

	public:
		RawModel* loadToVao(const std::vector<float>& positions, const std::vector<float>& textureCoords, const std::vector<int>& indices);
		unsigned int loadTexture(const char* filePath);
		void cleanUp();

	private:
		VertexArrayObject* createVAO();
		void storeDataInAttributeList(const int attributeNumber, const int coordinateSize, const std::vector<float>& data);
		void bindIndicesBuffer(const std::vector<int>& indices);

	};

}
