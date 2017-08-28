#include "Loader.h"

namespace Pressure {

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
		VertexBufferObject* vbo = new VertexBufferObject();
		vbo->generate();
		vbos.push_back(vbo);
		vbo->bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, 0);
		vbo->unbind();
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
	}

}
