#include "ParticleTexture.h"

namespace Pressure {

	ParticleTexture::ParticleTexture(const unsigned int textureID, const unsigned int numberOfRows, const bool additiveBlending)
		: m_Texture(textureID), m_NumberOfRows(numberOfRows), m_UseAdditiveBlending(additiveBlending) {
	}

	unsigned int ParticleTexture::getTextureID() const {
		return m_Texture;
	}

	unsigned int ParticleTexture::getNumberOfRows() const {
		return m_NumberOfRows;
	}

	bool ParticleTexture::isUseAdditiveBlending() const {
		return m_UseAdditiveBlending;
	}

	bool operator<(const ParticleTexture& left, const ParticleTexture& right) {
		return left.m_Texture < right.m_Texture;
	}

}
