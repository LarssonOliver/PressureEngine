#include "../../Constants.h"
#include "Particle.h"
#include "ParticleMaster.h"

namespace Pressure {

	Particle::Particle(ParticleTexture& texture, Vector3f& position, Vector3f& speed, float gravityEffect, float lifeLength, float rotation, float scale)
		: texture(texture),  position(position), speed(speed), gravityEffect(gravityEffect), lifeLength(lifeLength), rotation(rotation), scale(scale), elapsedTicks(0) {
		ParticleMaster::addParticle(*this);
	}

	bool Particle::isAlive(Camera& camera) {
		speed.y -= PRESSURE_GRAVITY * gravityEffect * elapsedTicks * PRESSURE_TICKTIME;
		position.add(speed);
		distance = camera.getPosition().sub(position, Vector3f()).lengthSquared();
		updateTextureCoordInfo();
		elapsedTicks++;
		return elapsedTicks < lifeLength;
	}

	ParticleTexture& Particle::getTexture() {
		return texture;
	}

	Vector3f& Particle::getPosition() {
		return position;
	}

	float Particle::getRotation() const {
		return rotation;
	}

	float Particle::getScale() const {
		return scale;
	}

	Vector2f& Particle::getCurrentUV() {
		return currentUV;
	}

	Vector2f& Particle::getBlendUV() {
		return blendUV;
	}

	float Particle::getBlend() const {
		return blend;
	}

	float Particle::getDistance() const {
		return distance;
	}

	void Particle::updateTextureCoordInfo() {
		int stageCount = texture.getNumberOfRows() * texture.getNumberOfRows();
		float atlasProgression = elapsedTicks / lifeLength * stageCount;
		int index = (int)atlasProgression;
		blend = std::fmod(atlasProgression, 1);
		setTextureOffset(currentUV, index);
		setTextureOffset(blendUV, index + 1);
	}

	void Particle::setTextureOffset(Vector2f& offset, int index) {
		index = index > 15 ? 15 : index;
		offset.setX((index % texture.getNumberOfRows()) / (float)texture.getNumberOfRows());
		offset.setY((index / texture.getNumberOfRows()) / (float)texture.getNumberOfRows());
	}

	bool operator<(const Particle& first, const Particle& second) {
		return first.getDistance() < second.getDistance();
	}

}
