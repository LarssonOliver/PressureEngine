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

	RawModel Loader::loadToVao(const std::vector<float>& positions, const std::vector<float>& textureCoords, const std::vector<float>& normals, const std::vector<unsigned int>& indices) {
		VertexBufferLayout layout;
		layout.push<float>(3, VertexBuffer(&positions[0], positions.size() * sizeof(float)));
		layout.push<float>(2, VertexBuffer(&textureCoords[0], positions.size() * sizeof(float)));
		layout.push<float>(3, VertexBuffer(&normals[0], positions.size() * sizeof(float)));
		VertexArray va;
		m_IndexBuffers.emplace_back(&indices[0], indices.size());
		va.bindLayout(layout);
		m_VertexBufferLayouts.push_back(layout);
		va.unbind();
		m_VertexArrays.push_back(va);
		Vector3f max;
		Vector3f min;
		for (int i = 0; i < positions.size() / 3; i++) {
			if (max.x < positions[i])
				max.x = positions[i];
			if (min.x > positions[i])
				min.x = positions[i];
			if (max.y < positions[i + 1])
				max.y = positions[i + 1];
			if (min.y > positions[i + 1])
				min.y = positions[i + 1];
			if (max.z < positions[i + 2])
				max.z = positions[i + 2];
			if (min.z > positions[i + 2])
				min.z = positions[i + 2];
		}
		return RawModel(va, indices.size(), Box(min, max));
	}

	RawModel Loader::loadToVao(const std::vector<float>& positions, const std::vector<unsigned int>& indices) {
		VertexBufferLayout layout;
		layout.push<float>(3, VertexBuffer(&positions[0], positions.size() * sizeof(float)));
		VertexArray va;
		m_IndexBuffers.emplace_back(&indices[0], indices.size());
		va.bindLayout(layout);
		m_VertexBufferLayouts.push_back(layout);
		va.unbind();
		m_VertexArrays.push_back(va);		
		Vector3f max;
		Vector3f min;
		for (int i = 0; i < positions.size() / 3; i++) {
			if (max.x < positions[i])
				max.x = positions[i];
			if (min.x > positions[i])
				min.x = positions[i];
			if (max.y < positions[i + 1])
				max.y = positions[i + 1];
			if (min.y > positions[i + 1])
				min.y = positions[i + 1];
			if (max.z < positions[i + 2])
				max.z = positions[i + 2];
			if (min.z > positions[i + 2])
				min.z = positions[i + 2];
		}
		return RawModel(va, indices.size(), Box(min, max));
	}

	RawModel Loader::loadToVao(const std::vector<float>& positions, const unsigned int dimensions) {
		VertexBufferLayout layout;
		layout.push<float>(dimensions, VertexBuffer(&positions[0], positions.size() * sizeof(float)));
		VertexArray va;
		va.bindLayout(layout);
		m_VertexBufferLayouts.push_back(layout);
		va.unbind();
		m_VertexArrays.push_back(va);
		Vector3f max;
		Vector3f min;
		for (int i = 0; i < positions.size() / dimensions; i++) {
			if (max.x < positions[i])
				max.x = positions[i];
			if (min.x > positions[i])
				min.x = positions[i];
			if (max.y < positions[i + 1])
				max.y = positions[i + 1];
			if (min.y > positions[i + 1])
				min.y = positions[i + 1];
			if (dimensions > 2) {
				if (max.z < positions[i + 2])
					max.z = positions[i + 2];
				if (min.z > positions[i + 2])
					min.z = positions[i + 2];
			}
		}
		return RawModel(va, positions.size() / dimensions, Box(min, max));
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
