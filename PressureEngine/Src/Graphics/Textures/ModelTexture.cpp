#include "ModelTexture.h"

namespace Pressure {

	ModelTexture::ModelTexture(unsigned int id)
		: textureID(id), shineDamper(1), reflectivity(0), hasTransparency(false), useFakeLighting(false) {
	}

	unsigned int ModelTexture::getID() const {
		return textureID;
	}

	float ModelTexture::getShineDamper() const {
		return shineDamper;
	}

	void ModelTexture::setShineDamper(const float shineDamper) {
		this->shineDamper = shineDamper;
	}

	float ModelTexture::getReflectivity() const {
		return reflectivity;
	}

	void ModelTexture::setReflectivity(const float reflectivity) {
		this->reflectivity = reflectivity;
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
