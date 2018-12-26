#include "GuiTexture.h"

namespace Pressure {

	GuiTexture::GuiTexture(unsigned int texture, Vector2f& position, Vector2f& scale, bool isTexture)
		: m_Texture(texture), m_Position(position), m_Scale(scale), m_IsTexture(isTexture) {
	}

	unsigned int GuiTexture::getTexture() const {
		return m_Texture;
	}

	Vector2f& GuiTexture::getPosition() {
		return m_Position;
	}

	Vector2f& GuiTexture::getScale() {
		return m_Scale;
	}

	bool GuiTexture::isTextureManaged() const {
		return m_IsTexture;
	}

}
