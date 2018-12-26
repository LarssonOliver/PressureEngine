#include "Entity.h"
#include <iostream>

namespace Pressure {

	Entity::Entity(const TexturedModel& model, const Vector3f& position, const Vector3f& rotation, const float scale)
		: m_Model(TexturedModel(model.getRawModel(), model.getTexture())), m_Rotation(rotation), m_RotationSpeed(0), m_Scale(scale), m_Bounds(model.getRawModel().getBounds().transform(position).scale(scale)), m_Position(position), m_Speed(Vector3f(0)), m_Acceleration(Vector3f(0))
	{}

	void Entity::tick() {
		m_Speed.add(m_Acceleration);
		m_Position.add(m_Speed);
		m_Rotation.add(m_RotationSpeed);
	}

	TexturedModel Entity::getTexturedModel() const {
		return m_Model;
	}

	Vector3f Entity::getRotation() const {
		return m_Rotation;
	}

	Vector3f Entity::getRotationSpeed() const {
		return m_RotationSpeed;
	}

	float Entity::getScale() const {
		return this->m_Scale;
	}

	AABB Entity::getBounds() const {
		return m_Bounds;
	}

	Vector3f Entity::getPosition() const {
		return m_Position;
	}

	Vector3f Entity::getSpeed() const {
		return m_Speed;
	}

	Vector3f Entity::getAcceleration() const {
		return m_Acceleration;
	}

	void Entity::rotate(const float x, const float y, const float z) {
		m_Rotation.add(x, y, z);
	}

	void Entity::setRotation(const float x, const float y, const float z) {
		m_Rotation.set(x, y, z);
	}

	void Entity::setRotationSpeed(const float x, const float y, const float z) {
		m_RotationSpeed.set(x, y, z);
	}

	void Entity::addScale(const float xyz) {
		m_Scale += xyz;
	}

	void Entity::setScale(const float xyz) {
		this->m_Scale = xyz;
	}

	void Entity::move(const float x, const float y, const float z) {
		m_Position.add(x, y, z);
	}

	void Entity::setPosition(const float x, const float y, const float z) {
		m_Position.set(x, y, z);
	}

	void Entity::setSpeed(const float x, const float y, const float z) {
		m_Speed.set(x, y, z);
	}

	void Entity::setAcceleration(const float x, const float y, const float z) {
		m_Acceleration.set(x, y, z);
	}

}