#include "Particles.hpp"
#include <algorithm>

Particle::Particle(glm::vec2 position, glm::vec2 velocity, glm::vec4 RGBA, float duration):
	position(position), velocity(velocity), RGBA(RGBA), duration(duration)
{
}


void Particle::Update(const float& dt)
{
	duration -= dt;
}


ParticleEmitter::ParticleEmitter(const glm::vec2& position, const float& particleDuration, const int& emitRate, const float& emitInterval):
	position(position), particleDuration(particleDuration), emitRate(emitRate), emitInterval(emitInterval), emitDuration(), particleList(), aliveParticles()
{
}


void ParticleEmitter::Update(const float& dt)
{
	for (int i = 0; i < aliveParticles; ++i)
	{
		if (particleList[i]->duration <= 0)
		{
			delete particleList[i];
			particleList[i] = nullptr;
			--aliveParticles;

			std::swap(particleList[i - 1], particleList[aliveParticles]);
		}
	}
}


void ParticleEmitter::AddParticles()
{
	for (int i = 0; i < emitRate; ++i)
	{
		particleList[aliveParticles] = new Particle(position, glm::vec2{ 0, 5 }, glm::vec4{1, 1, 1, 1}, particleDuration);
		++aliveParticles;
	}
}