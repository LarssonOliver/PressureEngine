#pragma once
#include "../Common.h"
#include "RawModel.h"

namespace Pressure {

	class Loader {

	private:
		std::vector<unsigned int> vaos;
		std::vector<unsigned int> vbos;
		std::vector<RawModel*> rawModels;

	public:
		RawModel* loadToVao(const std::vector<float>& positions);
		void cleanUp();

	private:
		int createVAO();
		void storeDataInAttributeList(int attributeNumber, const std::vector<float>& data);
		void unbindVAO() const;

	};

}
