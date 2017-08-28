#include "Loader.h"

namespace Pressure {

	// TODO: return type?
	RawModel* Loader::loadToVao(const std::vector<float>& positions) {
		int vaoID = createVAO();
		storeDataInAttributeList(0, positions);
		unbindVAO();
		RawModel* model = new RawModel(vaoID, positions.size() / 3);
		rawModels.push_back(model);
		return model;
	}

	int Loader::createVAO() {
		unsigned int vaoID;
		glGenVertexArrays(1, &vaoID);
		vaos.push_back(vaoID);
		glBindVertexArray(vaoID);
		return vaoID;
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

	void Loader::unbindVAO() const {
		glBindVertexArray(0);
	}

	void Loader::cleanUp() {
		for (unsigned i = 0; i < vaos.size(); i++) {
			glDeleteVertexArrays(1, &vaos[i]);
		}
		for (unsigned i = 0; i < vbos.size(); i++) {
			glDeleteBuffers(1, &vbos[i]);
		}
		for (unsigned i = 0; i < rawModels.size(); i++) {
			delete rawModels[i];
		}
	}

}
