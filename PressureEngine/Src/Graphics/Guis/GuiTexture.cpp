#include "GuiTexture.h"

namespace Pressure {

	GuiTexture::GuiTexture(unsigned int texture, Vector2f& position, Vector2f& scale, bool isTexture)
		: texture(texture), position(position), scale(scale), isTexture(isTexture) {
	}

	unsigned int GuiTexture::getTexture() const {
		return texture;
	}

	Vector2f& GuiTexture::getPosition() {
		return position;
	}

	Vector2f& GuiTexture::getScale() {
		return scale;
	}

	bool GuiTexture::isTextureManaged() const {
		return isTexture;
	}

}
