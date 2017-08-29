#include "TexturedModel.h"

namespace Pressure {

	TexturedModel::TexturedModel(RawModel* model, ModelTexture* texture)
		: rawModel(model), texture(texture) {
	}

	TexturedModel::~TexturedModel() {
		//delete rawModel;
		//delete texture;
	}

	RawModel* TexturedModel::getRawModel() const {
		return rawModel;
	}

	ModelTexture* TexturedModel::getTexture() const {
		return texture;
	}

}