#pragma once
#include "../Models/RawModel.h"
#include "../Textures/ModelTexture.h"
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API TexturedModel {

	private:
		RawModel m_RawModel;
		ModelTexture m_Texture;

	public:
		TexturedModel(RawModel model, ModelTexture texture)
			: m_RawModel(model), m_Texture(texture) { }

		inline RawModel getRawModel() const { return m_RawModel; }
		inline ModelTexture getTexture() const { return m_Texture; }

		inline bool operator==(const TexturedModel& other) const {
			return m_RawModel.getVertexArray().getID() == other.m_RawModel.getVertexArray().getID() && m_Texture.getID() == m_Texture.getID();
		}

	};

}

// Needed for comparisons when used as key in std::unordered_map.
namespace std {

	template <>
	struct hash<Pressure::TexturedModel> {
		size_t operator()(const Pressure::TexturedModel& m) const {
			size_t res = 17;
			res = res * 31 + hash<unsigned int>()(m.getRawModel().getVertexArray().getID());
			res = res * 31 + hash<unsigned int>()(m.getTexture().getID());
			return res;
		}
	};

}