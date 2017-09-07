#pragma once

namespace Pressure {

	class ModelTexture {

	private:
		unsigned int textureID;
		bool hasTransparency;
		bool useFakeLighting;

	public:
		ModelTexture(unsigned int id);
		unsigned int getID() const;
		
		bool isHasTransparency() const;
		void setHasTransparency(const bool transparency);

		bool isUseFakeLighting() const;
		void setUseFakeLighting(const bool fakeLighting);

	};

}