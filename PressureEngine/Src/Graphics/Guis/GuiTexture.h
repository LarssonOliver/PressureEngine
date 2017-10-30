#pragma once
#include "../../Math/Vectors/Vector2f.h"

namespace Pressure {

	class GuiTexture {

	private:
		const unsigned int texture;
		Vector2f position;
		Vector2f scale;

	public:
		GuiTexture(unsigned int texture, Vector2f& position, Vector2f& scale);
		unsigned int getTexture() const;
		Vector2f& getPosition();
		Vector2f& getScale();

	};

}