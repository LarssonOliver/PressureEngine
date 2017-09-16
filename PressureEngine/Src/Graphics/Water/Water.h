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
		static RawModel* model;

	public:
		Water(Vector3f& position, Loader& loader);

		RawModel* getModel();
		Vector3f& getPosition();

	private:
		RawModel* generateWater(Loader& loader);

	};

}