#include "Loader.h"
#include <string>
#include "Textures\TextureManager.h"

namespace Pressure {
		
	Loader::~Loader() {
		for (auto& array : m_VertexArrays) {
			array.del();
		}
		for (auto& layout : m_VertexBufferLayouts) {
			for (auto& element : layout.getElements()) {
				element.buffer.del();
			}
		}
		for (auto& buffer : m_IndexBuffers) {
			buffer.del();
		}
		TextureManager::Inst()->UnloadAllTextures();
	}

	RawModel Loader::loadToVao(const VertexBuffer& positions, const VertexBuffer& textureCoords, const VertexBuffer& normals, const std::vector<unsigned int>& indices) {
		VertexBufferLayout layout;
		layout.push<float>(3, positions);
		layout.push<float>(2, textureCoords);
		layout.push<float>(3, normals);
		VertexArray va;
		m_IndexBuffers.emplace_back(&indices[0], indices.size());
		va.bindLayout(layout);
		m_VertexBufferLayouts.push_back(layout);
		va.unbind();
		m_VertexArrays.push_back(va);
		return RawModel(va, indices.size());
	}

	RawModel Loader::loadToVao(const VertexBuffer& positions, const std::vector<unsigned int>& indices) {
		VertexBufferLayout layout;
		layout.push<float>(3, positions);
		VertexArray va;
		m_IndexBuffers.emplace_back(&indices[0], indices.size());
		va.bindLayout(layout);
		m_VertexBufferLayouts.push_back(layout);
		va.unbind();
		m_VertexArrays.push_back(va);
		return RawModel(va, indices.size());
	}

	RawModel Loader::loadToVao(const std::vector<float>& positions, const unsigned int dimensions) {
		VertexBufferLayout layout;
		layout.push<float>(dimensions, VertexBuffer(&positions[0], positions.size()));
		VertexArray va;
		va.bindLayout(layout);
		m_VertexBufferLayouts.push_back(layout);
		va.unbind();
		m_VertexArrays.push_back(va);
		return RawModel(va, positions.size() / dimensions);
	}

	unsigned int Loader::loadTexture(const char* filePath) {
		unsigned int newTextureID = m_Textures.size();
		if (!TextureManager::Inst()->LoadTexture((std::string("Res/") + filePath).c_str(), newTextureID)) {
			return NULL;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1);
		m_Textures.push_back(newTextureID);
		return newTextureID;
	}

	unsigned int Loader::loadCubeMap(const char* filePath) {
		unsigned int newTextureID = m_Textures.size();
		std::vector<std::string> fileNames;

		for (int i = 0; i < 6; i++)
			fileNames.emplace_back(std::string("Res/") + filePath + '_' + (char)(48 + i) + ".png");

		if (!TextureManager::Inst()->LoadCubeMap(fileNames, newTextureID)) {
			return NULL;
		}
		m_Textures.push_back(newTextureID);
		return newTextureID;
	}

}
