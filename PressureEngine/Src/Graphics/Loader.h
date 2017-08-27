#pragma once
#include "../Common.h"
#include "RawModel.h"

namespace Pressure {

	class Loader {

	public:
		RawModel& loadToVao(const std::vector<float>& positions);

	private:
		int createVAO();
		void storeDataInAttributeList(int attributeNumber, const std::vector<float>& data);
		void unbindVAO();

	};

}
