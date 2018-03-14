#pragma once
#include "../Models/TexturedModel.h"
#include "../../Math/Math.h"
#include "../../DllExport.h"

namespace Pressure {

	class PRESSURE_API Entity {

	private:
		TexturedModel m_Model;
		Vector3f m_Rotation;
		Vector3f m_RotationSpeed;
		float m_Scale;

		AABB m_Bounds;

		Vector3f m_Position;
		Vector3f m_Speed;
		Vector3f m_Acceleration;

	public:
		Entity(const TexturedModel& model, const Vector3f& position, const Vector3f& rotation, const float scale);

		void tick();

		TexturedModel getTexturedModel() const;
		Vector3f getRotation() const;
		Vector3f getRotationSpeed() const;
		float getScale() const;

		AABB getBounds() const;

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