#pragma once
#include "../Models/TexturedModel.h"
#include "../../Math/Math.h"

namespace Pressure {

	class Entity {

	private:
		TexturedModel model;
		Vector3f rotation;
		Vector3f rotationSpeed;
		float scale;

		Vector3f position;
		Vector3f speed;
		Vector3f acceleration;

	public:
		Entity(const TexturedModel& model, const Vector3f& position, const Vector3f& rotation, const float scale);

		void tick();

		TexturedModel getTexturedModel() const;
		Vector3f getRotation() const;
		Vector3f getRotationSpeed() const;
		float getScale() const;

		Vector3f getPosition() const;
		Vector3f getSpeed() const;
		Vector3f getAcceleration() const;

		void rotate(const float x, const float y, const float z);
		void setRotation(const float x, const float y, const float z);
		void setRotationSpeed(const float x, const float y, const float z);

		void addScale(const float xyz);
		void setScale(const float xyz);

		void move(const float x, const float y, const float z);
		void setPosition(const float x, const float y, const float z);
		void setSpeed(const float x, const float y, const float z);
		void setAcceleration(const float x, const float y, const float z);

	};

}