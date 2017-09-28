#include "ParticleTexture.h"

namespace Pressure {

	ParticleTexture::ParticleTexture(const int textureID, const int numberOfRows, const bool additiveBlending)
		: textureID(textureID), numberOfRows(numberOfRows), useAdditiveBlending(additiveBlending) {
	}

	int ParticleTexture::getTextureID() const {
		return textureID;
	}

	int ParticleTexture::getNumberOfRows() const {
		return numberOfRows;
	}

	bool ParticleTexture::isUseAdditiveBlending() const {
		return useAdditiveBlending;
	}

	bool operator<(const ParticleTexture& left, const ParticleTexture& right) {
		return left.textureID < right.textureID;
	}

}
