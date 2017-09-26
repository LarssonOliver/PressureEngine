#pragma once
#include "../../Math/Vectors/Vector3f.h"
#include "../../Math/Vectors/Vector2f.h"
#include "ParticleTexture.h"
#include "../Entities/Camera.h"

namespace Pressure {

	class Particle {

	private:
		Vector3f position;
		Vector3f speed;
		float gravityEffect;
		float lifeLength;
		float rotation;
		float scale;
		float elapsedTicks;

		// For depth checking.
		float distance;

		ParticleTexture& texture;

		Vector2f currentUV;
		Vector2f blendUV;
		float blend;

	public:
		Particle(ParticleTexture& texture, Vector3f& position, Vector3f& speed, float gravityEffect, float lifeLength, float rotation, float scale);

		// Called once every tick, updates particle and returns false if particle should die.
		bool isAlive(Camera& camera);

		ParticleTexture& getTexture();
		Vector3f& getPosition();
		float getRotation() const;
		float getScale() const;
		Vector2f& getCurrentUV();
		Vector2f& getBlendUV();
		float getBlend() const;
		float getDistance() const;

	private:
		void updateTextureCoordInfo();
		void setTextureOffset(Vector2f& offset, int index);

	};

}