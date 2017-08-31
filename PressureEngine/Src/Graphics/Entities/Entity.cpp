#include "Entity.h"

namespace Pressure {

	Entity::Entity(const TexturedModel& model, const Vector3f& position, const Vector3f& rotation, const float scale)
		: model(TexturedModel(model.getRawModel(), model.getTexture())), rotation(rotation), scale(scale), position(position), speed(Vector3f(0)), acceleration(Vector3f(0))
	{}

	void Entity::tick() {
		speed.add(acceleration);
		position.add(speed);
	}

	TexturedModel& Entity::getTexturedModel() {
		return model;
	}

	Vector3f& Entity::getRotation() {
		return rotation;
	}

	float Entity::getScale() const {
		return scale;
	}

	Vector3f& Entity::getPosition() {
		return position;
	}

	Vector3f& Entity::getSpeed() {
		return speed;
	}

	Vector3f& Entity::getAcceleration(){
		return acceleration;
	}

}