#pragma once
#include "../../Math/Vectors/Vector3f.h"
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API Light {

	private:
		Vector3f m_Position;
		Vector3f m_Color;
		Vector3f m_Attenuation;

	public:
		Light(const Vector3f& position, const Vector3f& color, const Vector3f& attenuation = Vector3f(1, 0, 0));

		Vector3f& getPosition();
		Vector3f& getColor();
		Vector3f& getAttenuation();

	};

}