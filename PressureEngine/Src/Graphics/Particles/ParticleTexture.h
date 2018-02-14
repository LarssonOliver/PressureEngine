#pragma once

#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API ParticleTexture {

	private:
		int textureID;
		int numberOfRows;
		bool useAdditiveBlending;

	public:
		ParticleTexture(const int textureID, const int numberOfRows, const bool additiveBlending = false);

	public:
		int getTextureID() const;
		int getNumberOfRows() const;
		bool isUseAdditiveBlending() const;

		friend bool operator<(const ParticleTexture& left, const ParticleTexture& right);

	};

}