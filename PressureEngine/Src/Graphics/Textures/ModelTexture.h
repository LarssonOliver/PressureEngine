#pragma once

namespace Pressure {

	class ModelTexture {

	private:
		unsigned int textureID;

	public:
		ModelTexture(unsigned int id);
		unsigned int getID() const;

	};

}