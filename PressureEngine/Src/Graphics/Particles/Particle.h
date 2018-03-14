#pragma once
#include "../../Math/Vectors/Vector3f.h"
#include "../../Math/Vectors/Vector2f.h"
#include "ParticleTexture.h"
#include "../Entities/Camera.h"

namespace Pressure {

	class Particle {

	private:
		Vector3f m_Position;
		Vector3f m_Speed;
		float m_GravityEffect;
		float m_LifeLength;
		float m_Rotation;
		float m_Scale;
		float m_ElapsedTicks;

		// For depth checking.
		float m_Distance;

		ParticleTexture& m_Texture;

		Vector2f m_CurrentUV;
		Vector2f m_BlendUV;
		float m_Blend;

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