#pragma once
#include "../../Math/Vectors/Vector3f.h"

namespace Pressure {

	class Light {

	private:
		Vector3f position;
		Vector3f color;

	public:
		Light(Vector3f& position, Vector3f& color);

		Vector3f& getPosition();
		Vector3f& getColor();

	};

}