#pragma once

#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API ParticleTexture {

	private:
		unsigned int m_Texture;
		unsigned int m_NumberOfRows;
		bool m_UseAdditiveBlending;

	public:
		ParticleTexture(const unsigned int textureID, const unsigned int numberOfRows, const bool additiveBlending = false);

	public:
		unsigned int getTextureID() const;
		unsigned int getNumberOfRows() const;
		bool isUseAdditiveBlending() const;

		friend bool operator<(const ParticleTexture& left, const ParticleTexture& right);

	};

}