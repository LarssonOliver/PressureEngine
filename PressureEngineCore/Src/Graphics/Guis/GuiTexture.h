#pragma once

#include "../../DllExport.h"
#include "../../Math/Vectors/Vector2f.h"

namespace Pressure {

	class PRESSURE_API GuiTexture {

	private:
		unsigned int m_Texture;
		Vector2f m_Position;
		Vector2f m_Scale;
		bool m_IsTexture;

	public:
		GuiTexture(unsigned int texture, Vector2f& position, Vector2f& scale, bool isTexture = true);
		unsigned int getTexture() const;
		Vector2f& getPosition();
		Vector2f& getScale();
		bool isTextureManaged() const;

	};

}