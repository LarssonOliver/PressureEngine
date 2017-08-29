#pragma once
#include "../GraphicsCommon.h"

namespace Pressure {

	class TexturedModel {

	private:
		RawModel* rawModel;
		ModelTexture* texture;

	public:
		TexturedModel(RawModel* model, ModelTexture* texture);
		~TexturedModel();
		RawModel* getRawModel() const;
		ModelTexture* getTexture() const;

	};

}