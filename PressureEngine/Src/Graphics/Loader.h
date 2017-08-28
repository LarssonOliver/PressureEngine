#pragma once
#include "../Common.h"
#include "GraphicsCommon.h"

namespace Pressure {

	class Loader {

	private:
		std::vector<VertexArrayObject*> vaos;
		std::vector<VertexBufferObject*> vbos;
		std::vector<RawModel*> rawModels;

	public:
		RawModel* loadToVao(const std::vector<float>& positions);
		void cleanUp();

	private:
		VertexArrayObject* createVAO();
		void storeDataInAttributeList(int attributeNumber, const std::vector<float>& data);

	};

}
