#pragma once
#include <memory>
#include "../Models/RawModel.h"
#include "../Loader.h"

namespace Pressure {

	class Water {

	private:
		static const int SIZE;
		static const int VERTEX_COUNT;

		Vector3f position;
		static RawModel model;

	public:
		Water(const Vector3f& position, Loader& loader);

		static RawModel getModel();
		Vector3f& getPosition();

	private:
		RawModel generateWater(Loader& loader);

	};

}