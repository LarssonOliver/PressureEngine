#include "ModelTexture.h"

namespace Pressure {

	ModelTexture::ModelTexture(unsigned int id) {
		textureID = id;
	}

	unsigned int ModelTexture::getID() const {
		return textureID;
	}

}
