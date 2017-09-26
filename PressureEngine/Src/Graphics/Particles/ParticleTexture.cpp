#include "ParticleTexture.h"

namespace Pressure {

	ParticleTexture::ParticleTexture(const int textureID, const int numberOfRows) 
		: textureID(textureID), numberOfRows(numberOfRows) {
	}

	int ParticleTexture::getTextureID() const {
		return textureID;
	}

	int ParticleTexture::getNumberOfRows() const {
		return numberOfRows;
	}

	bool operator<(const ParticleTexture& left, const ParticleTexture& right) {
		return left.textureID < right.textureID;
	}

}
