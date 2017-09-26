#pragma once

namespace Pressure {

	class ParticleTexture {

	private:
		int textureID;
		int numberOfRows;

	public:
		ParticleTexture(const int textureID, const int numberOfRows);

	public:
		int getTextureID() const;
		int getNumberOfRows() const;

		friend bool operator<(const ParticleTexture& left, const ParticleTexture& right);

	};

}