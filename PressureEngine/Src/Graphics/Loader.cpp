#include "Loader.h"

namespace Pressure {

	// TODO: return type?
	RawModel* Loader::loadToVao(const std::vector<float>& positions) {
		VertexArrayObject* vao = createVAO();
		storeDataInAttributeList(0, positions);
		vao->unbind();
		RawModel* model = new RawModel(vao, positions.size() / 3);
		rawModels.push_back(model);
		return model;
	}

	VertexArrayObject* Loader::createVAO() {
		VertexArrayObject* vao = new VertexArrayObject();
		vao->generate();
		vaos.push_back(vao);
		vao->bind();
		return vao;
	}

	void Loader::storeDataInAttributeList(int attributeNumber, const std::vector<float>& data) {
		unsigned int vboID;
		glGenBuffers(1, &vboID);
		vbos.push_back(vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Loader::cleanUp() {
		for (unsigned i = 0; i < vaos.size(); i++) {
			vaos[i]->cleanUp();
			delete vaos[i];
		}
		for (unsigned i = 0; i < vbos.size(); i++) {
			glDeleteBuffers(1, &vbos[i]);
		}
		for (unsigned i = 0; i < rawModels.size(); i++) {
			delete rawModels[i];
		}
	}

}
