#pragma once
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API ModelTexture {

	private:
		unsigned int textureID;

		float shineDamper;
		float reflectivity;

		bool hasTransparency;
		bool useFakeLighting;

	public:
		ModelTexture(unsigned int id);
		unsigned int getID() const;
		
		float getShineDamper() const;
		void setShineDamper(const float shineDamper);

		float getReflectivity() const;
		void setReflectivity(const float reflectivity);

		bool isHasTransparency() const;
		void setHasTransparency(const bool transparency);

		bool isUseFakeLighting() const;
		void setUseFakeLighting(const bool fakeLighting);

	};

}