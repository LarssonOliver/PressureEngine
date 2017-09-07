#include "ModelTexture.h"

namespace Pressure {

	ModelTexture::ModelTexture(unsigned int id) 
		: textureID(id), hasTransparency(false) {
	}

	unsigned int ModelTexture::getID() const {
		return textureID;
	}

	bool ModelTexture::isHasTransparency() const {
		return hasTransparency;
	}

	void ModelTexture::setHasTransparency(const bool transparency) {
		hasTransparency = transparency;
	}

	bool ModelTexture::isUseFakeLighting() const {
		return useFakeLighting;
	}

	void ModelTexture::setUseFakeLighting(const bool fakeLighting) {
		useFakeLighting = fakeLighting;
	}
	
}
