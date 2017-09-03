#include "Entity.h"
#include <iostream>

namespace Pressure {

	Entity::Entity(const TexturedModel& model, const Vector3f& position, const Vector3f& rotation, const float scale)
		: model(TexturedModel(model.getRawModel(), model.getTexture())), rotation(rotation), rotationSpeed(0), scale(scale), position(position), speed(Vector3f(0)), acceleration(Vector3f(0))
	{}

	void Entity::tick() {
		speed.add(acceleration);
		position.add(speed);
		rotation.add(rotationSpeed);
	}

	TexturedModel Entity::getTexturedModel() const {
		return model;
	}

	Vector3f Entity::getRotation() const {
		return rotation;
	}

	Vector3f Entity::getRotationSpeed() const {
		return rotationSpeed;
	}

	float Entity::getScale() const {
		return this->scale;
	}

	Vector3f Entity::getPosition() const {
		return position;
	}

	Vector3f Entity::getSpeed() const {
		return speed;
	}

	Vector3f Entity::getAcceleration() const {
		return acceleration;
	}

	void Entity::rotate(const float x, const float y, const float z) {
		rotation.add(x, y, z);
	}

	void Entity::setRotation(const float x, const float y, const float z) {
		rotation.set(x, y, z);
	}

	void Entity::setRotationSpeed(const float x, const float y, const float z) {
		rotationSpeed.set(x, y, z);
	}

	void Entity::addScale(const float xyz) {
		scale += xyz;
	}

	void Entity::setScale(const float xyz) {
		this->scale = xyz;
	}

	void Entity::move(const float x, const float y, const float z) {
		position.add(x, y, z);
	}

	void Entity::setPosition(const float x, const float y, const float z) {
		position.set(x, y, z);
	}

	void Entity::setSpeed(const float x, const float y, const float z) {
		speed.set(x, y, z);
	}

	void Entity::setAcceleration(const float x, const float y, const float z) {
		acceleration.set(x, y, z);
	}

}