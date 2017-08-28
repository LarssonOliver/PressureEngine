#pragma once
#include "../Common.h"
#include "RawModel.h"
#include "VertexObjects\VertexArrayObject.h"

namespace Pressure {

	class Loader {

	private:
		std::vector<VertexArrayObject*> vaos;
		std::vector<unsigned int> vbos;
		std::vector<RawModel*> rawModels;

	public:
		RawModel* loadToVao(const std::vector<float>& positions);
		void cleanUp();

	private:
		VertexArrayObject* createVAO();
		void storeDataInAttributeList(int attributeNumber, const std::vector<float>& data);

	};

}
