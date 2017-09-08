#include "Loader.h"
#include <string>
#include "Textures\TextureManager.h"

namespace Pressure {

	RawModel* Loader::loadToVao(const std::vector<float>& positions, const std::vector<float>& textureCoords, const std::vector<float>& normals, const std::vector<int>& indices) {
		VertexArrayObject* vao = createVAO();
		bindIndicesBuffer(indices);
		storeDataInAttributeList(0, 3, positions);
		storeDataInAttributeList(1, 2, textureCoords);
		storeDataInAttributeList(2, 3, normals);
		vao->unbind();
		RawModel* model = new RawModel(vao, indices.size());
		rawModels.emplace_back(model);
		return model;
	}

	RawModel* Loader::loadToVao(const std::vector<float>& positions, const int dimensions) {
		VertexArrayObject* vao = createVAO();
		storeDataInAttributeList(0, dimensions, positions);
		vao->unbind();
		RawModel* model = new RawModel(vao, positions.size() / dimensions);
		rawModels.emplace_back(model);
		return model;
	}

	unsigned int Loader::loadTexture(const char* filePath) {
		unsigned int newTextureID = textures.size();
		if (!TextureManager::Inst()->LoadTexture((std::string("Res/") + filePath).c_str(), newTextureID)) {
			return NULL;
		}
		textures.emplace_back(newTextureID);
		return newTextureID;
	}

	unsigned int Loader::loadCubeMap(const char* filePath) {
		unsigned int newTextureID = textures.size();
		std::vector<std::string> fileNames(6);

		for (int i = 0; i < 6; i++)
			fileNames[i] = (std::string("Res/") + filePath + '_' + (char)(48 + i) + ".png");

		if (!TextureManager::Inst()->LoadCubeMap(fileNames, newTextureID)) {
			return NULL;
		}
		textures.emplace_back(newTextureID);
		return newTextureID;
	}

	VertexArrayObject* Loader::createVAO() {
		VertexArrayObject* vao = new VertexArrayObject();
		vao->generate();
		vaos.emplace_back(vao);
		vao->bind();
		return vao;
	}

	void Loader::storeDataInAttributeList(const int attributeNumber, const int coordinateSize, const std::vector<float>& data) {
		VertexBufferObject* vbo = new VertexBufferObject(GL_ARRAY_BUFFER);
		vbo->generate();
		vbos.emplace_back(vbo);
		vbo->bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, 0);
		vbo->unbind();
	}

	void Loader::bindIndicesBuffer(const std::vector<int>& indices) {
		VertexBufferObject* vbo = new VertexBufferObject(GL_ELEMENT_ARRAY_BUFFER);
		vbo->generate();
		vbos.emplace_back(vbo);
		vbo->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
	}

	void Loader::cleanUp() {
		for (unsigned i = 0; i < vaos.size(); i++) {
			vaos[i]->cleanUp();
			delete vaos[i];
		}
		for (unsigned i = 0; i < vbos.size(); i++) {
			vbos[i]->cleanUp();
			delete vbos[i];
		}
		for (unsigned i = 0; i < rawModels.size(); i++) {
			delete rawModels[i];
		}
		TextureManager::Inst()->UnloadAllTextures();
	}

}
