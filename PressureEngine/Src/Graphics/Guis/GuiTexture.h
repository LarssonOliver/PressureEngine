#pragma once
#include "../../Math/Vectors/Vector2f.h"

namespace Pressure {

	class GuiTexture {

	private:
		unsigned int texture;
		Vector2f position;
		Vector2f scale;
		bool isTexture;

	public:
		GuiTexture(unsigned int texture, Vector2f& position, Vector2f& scale, bool isTexture = true);
		unsigned int getTexture() const;
		Vector2f& getPosition();
		Vector2f& getScale();
		bool isTextureManaged() const;

	};

}