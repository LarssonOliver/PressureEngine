#pragma once
#include "../Models/RawModel.h"
#include "../Textures/ModelTexture.h"
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API TexturedModel {

	private:
		RawModel* rawModel;
		ModelTexture* texture;

	public:
		TexturedModel(RawModel* model, ModelTexture* texture);
		~TexturedModel();
		RawModel* getRawModel() const;
		ModelTexture* getTexture() const;

		// Needs to be implemented to be used as key in map;
		bool operator<(const TexturedModel& right) const;

	};

}