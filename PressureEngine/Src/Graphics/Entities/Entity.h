#pragma once
#include "../Models/TexturedModel.h"
#include "../../Math/Math.h"

namespace Pressure {

	class Entity {

	private:
		TexturedModel model;
		Vector3f rotation;
		float scale;

		Vector3f position;
		Vector3f speed;
		Vector3f acceleration;

	public:
		Entity(const TexturedModel& model, const Vector3f& position, const Vector3f& rotation, const float scale);

		void tick();

		TexturedModel& getTexturedModel();
		Vector3f& getRotation();
		float getScale() const;

		Vector3f& getPosition();
		Vector3f& getSpeed();
		Vector3f& getAcceleration();


	};

}