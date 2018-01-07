#pragma once
#include "../../Math/Vectors/Vector3f.h"

namespace Pressure {

	class Light {

	private:
		Vector3f position;
		Vector3f color;
		Vector3f attenuation;

	public:
		Light(Vector3f& position, Vector3f& color, Vector3f& attenuation = (Vector3f&) Vector3f(1, 0, 0));

		Vector3f& getPosition();
		Vector3f& getColor();
		Vector3f& getAttenuation();

	};

}