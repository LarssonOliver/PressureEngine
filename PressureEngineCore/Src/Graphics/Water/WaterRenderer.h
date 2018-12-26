#pragma once
#include <vector>
#include "../Models/RawModel.h"
#include "WaterShader.h"
#include "Water.h"
#include "../GLObjects/FrameBuffer.h"

namespace Pressure {

	class WaterRenderer {

	private:
		WaterShader m_Shader;
		Window& m_Window;
		float m_WaveModifier;

		FrameBuffer m_ReflectionBuffer;
		FrameBuffer m_RefractionBuffer;
		FrameBuffer m_ReflectionResultsBuffer;
		FrameBuffer m_RefractionResultsBuffer;

	public:
		WaterRenderer(Window& window);
		void updateProjectionmatrix();

		// Used to time the waves.
		void tick();
		void render(std::vector<Water>& water, std::vector<Light>& lights, Camera& camera);

		FrameBuffer& getReflectionBuffer();
		FrameBuffer& getRefractionBuffer();

	private:
		void prepare(std::vector<Water>& water, std::vector<Light>& lights, Camera& camera);
		void finish(std::vector<Water>& water);

	};

}
