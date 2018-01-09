#pragma once
#include "../../Math/Vectors/Vector3f.h"
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API Light {

	private:
		Vector3f position;
		Vector3f color;
		Vector3f attenuation;

	public:
		Light(const Vector3f& position, const Vector3f& color, const Vector3f& attenuation = Vector3f(1, 0, 0));

		Vector3f& getPosition();
		Vector3f& getColor();
		Vector3f& getAttenuation();

	};

}