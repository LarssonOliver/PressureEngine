#include "Light.h"

namespace Pressure {

	Light::Light(const Vector3f& position, const Vector3f& color, const Vector3f& attenuation)
		: m_Position(position), m_Color(color), m_Attenuation(attenuation)
	{ }

	Vector3f& Light::getPosition() {
		return m_Position;
	}

	Vector3f& Light::getColor() {
		return m_Color;
	}

	Vector3f& Light::getAttenuation() {
		return m_Attenuation;
	}

}
