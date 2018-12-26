#include "../../Constants.h"
#include "Particle.h"
#include "ParticleMaster.h"

namespace Pressure {

	Particle::Particle(ParticleTexture& texture, Vector3f& position, Vector3f& speed, float gravityEffect, float lifeLength, float rotation, float scale)
		: m_Texture(texture),  m_Position(position), m_Speed(speed), m_GravityEffect(gravityEffect), m_LifeLength(lifeLength), m_Rotation(rotation), m_Scale(scale), m_ElapsedTicks(0) {
		ParticleMaster::addParticle(*this);
	}

	bool Particle::isAlive(Camera& camera) {
		m_Speed.y -= PRESSURE_GRAVITY * m_GravityEffect * m_ElapsedTicks * PRESSURE_TICKTIME;
		m_Position.add(m_Speed);
		m_Distance = camera.getPosition().sub(m_Position, Vector3f()).lengthSquared();
		updateTextureCoordInfo();
		m_ElapsedTicks++;
		return m_ElapsedTicks < m_LifeLength;
	}

	ParticleTexture& Particle::getTexture() {
		return m_Texture;
	}

	Vector3f& Particle::getPosition() {
		return m_Position;
	}

	float Particle::getRotation() const {
		return m_Rotation;
	}

	float Particle::getScale() const {
		return m_Scale;
	}

	Vector2f& Particle::getCurrentUV() {
		return m_CurrentUV;
	}

	Vector2f& Particle::getBlendUV() {
		return m_BlendUV;
	}

	float Particle::getBlend() const {
		return m_Blend;
	}

	float Particle::getDistance() const {
		return m_Distance;
	}

	void Particle::updateTextureCoordInfo() {
		int stageCount = m_Texture.getNumberOfRows() * m_Texture.getNumberOfRows();
		float atlasProgression = m_ElapsedTicks / m_LifeLength * stageCount;
		int index = (int)atlasProgression;
		m_Blend = std::fmodf(atlasProgression, 1);
		setTextureOffset(m_CurrentUV, index);
		setTextureOffset(m_BlendUV, index < stageCount - 1 ? index + 1 : index);
	}

	void Particle::setTextureOffset(Vector2f& offset, int index) {
		offset.setX((index % m_Texture.getNumberOfRows()) / (float)m_Texture.getNumberOfRows());
		offset.setY((index / m_Texture.getNumberOfRows()) / (float)m_Texture.getNumberOfRows());
	}

	bool operator<(const Particle& first, const Particle& second) {
		return first.getDistance() < second.getDistance();
	}

}
