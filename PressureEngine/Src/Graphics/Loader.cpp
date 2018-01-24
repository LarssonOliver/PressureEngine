#include "Loader.h"
#include <string>
#include "Textures\TextureManager.h"

namespace Pressure {
		
	Loader::~Loader() {
		TextureManager::Inst()->UnloadAllTextures();
	}

	RawModel Loader::loadToVao(const VertexBuffer& positions, const VertexBuffer& textureCoords, const VertexBuffer& normals, const std::vector<unsigned int>& indices) {
		VertexBufferLayout layout;
		layout.push<float>(3, positions);
		layout.push<float>(2, textureCoords);
		layout.push<float>(3, normals);
		VertexArray va;
		IndexBuffer ib(&indices[0], indices.size());
		va.bindLayout(layout);
		va.unbind();
		return RawModel(va, indices.size());
	}

	RawModel Loader::loadToVao(const VertexBuffer& positions, const std::vector<unsigned int>& indices) {
		VertexBufferLayout layout;
		layout.push<float>(3, positions);
		VertexArray va;
		IndexBuffer ib(&indices[0], indices.size());
		return RawModel(va, indices.size());
	}

	RawModel Loader::loadToVao(const std::vector<float>& positions, const unsigned int dimensions) {
		VertexBufferLayout layout;
		layout.push<float>(dimensions, VertexBuffer(&positions[0], positions.size()));
		VertexArray va;
		va.bindLayout(layout);
		return RawModel(va, positions.size() / dimensions);
	}

	unsigned int Loader::loadTexture(const char* filePath) {
		unsigned int newTextureID = textures.size();
		if (!TextureManager::Inst()->LoadTexture((std::string("Res/") + filePath).c_str(), newTextureID)) {
			return NULL;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1);
		textures.push_back(newTextureID);
		return newTextureID;
	}

	unsigned int Loader::loadCubeMap(const char* filePath) {
		unsigned int newTextureID = textures.size();
		std::vector<std::string> fileNames;

		for (int i = 0; i < 6; i++)
			fileNames.emplace_back(std::string("Res/") + filePath + '_' + (char)(48 + i) + ".png");

		if (!TextureManager::Inst()->LoadCubeMap(fileNames, newTextureID)) {
			return NULL;
		}
		textures.push_back(newTextureID);
		return newTextureID;
	}

}
