#include "Light.h"

namespace Pressure {

	Light::Light(const Vector3f& position, const Vector3f& color, const Vector3f& attenuation)
		: position(position), color(color), attenuation(attenuation)
	{ }

	Vector3f& Light::getPosition() {
		return position;
	}

	Vector3f& Light::getColor() {
		return color;
	}

	Vector3f& Light::getAttenuation() {
		return attenuation;
	}

}
