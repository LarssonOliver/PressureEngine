#include "Light.h"

namespace Pressure {

	Light::Light(Vector3f& position, Vector3f& color)
		: position(position), color(color)
	{ }

	Vector3f& Light::getPosition() {
		return position;
	}

	Vector3f& Light::getColor() {
		return color;
	}

}
