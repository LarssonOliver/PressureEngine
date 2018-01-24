#pragma once
#include "../Models/RawModel.h"
#include "../Textures/ModelTexture.h"
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API TexturedModel {

	private:
		RawModel m_RawModel;
		ModelTexture* m_Texture;

	public:
		TexturedModel(RawModel model, ModelTexture* texture)
			: m_RawModel(model), m_Texture(texture) { }

		inline RawModel getRawModel() const { return m_RawModel; }
		inline ModelTexture* getTexture() const { return m_Texture; }

	};

}