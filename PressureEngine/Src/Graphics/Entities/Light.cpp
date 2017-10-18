#include "Light.h"

namespace Pressure {

	Light::Light(Vector3f& position, Vector3f& color, Vector3f& attenuation)
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
