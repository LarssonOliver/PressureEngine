#include "TexturedModel.h"

namespace Pressure {

	TexturedModel::TexturedModel(RawModel* model, ModelTexture* texture)
		: rawModel(model), texture(texture) {
	}

	TexturedModel::~TexturedModel() { }

	RawModel* TexturedModel::getRawModel() const {
		return rawModel;
	}

	ModelTexture* TexturedModel::getTexture() const {
		return texture;
	}

	bool TexturedModel::operator<(const TexturedModel& right) const {
		return rawModel->getVaoID() < right.getRawModel()->getVaoID();
	}

}