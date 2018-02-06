#pragma once
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API ModelTexture {

	private:
		unsigned int m_TextureID;

		float m_ShineDamper;
		float m_Reflectivity;

		bool m_Transparency;
		bool m_FakeLighting;

	public:
		ModelTexture(const unsigned int textureID)
			: m_TextureID(textureID), m_ShineDamper(1), m_Reflectivity(0), m_Transparency(false), m_FakeLighting(false) 
		{ }
		
		inline unsigned int getID() const { return m_TextureID; }
		
		inline float getShineDamper() const { return m_ShineDamper; }
		inline void setShineDamper(const float shineDamper) { m_ShineDamper = shineDamper; }

		inline float getReflectivity() const { return m_Reflectivity; }
		inline void setReflectivity(const float reflectivity) { m_Reflectivity = reflectivity; }

		inline bool hasTransparency() const { return m_Transparency; }
		inline void setTransparency(const bool transparency) { m_Transparency = transparency; }

		inline bool useFakeLighting() const { return m_FakeLighting; }
		inline void setFakeLighting(const bool fakeLighting) { m_FakeLighting = fakeLighting; }

	};

}