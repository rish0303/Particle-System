#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include<iostream>
#include <vector>
#include <glm/glm.hpp>

class Particle
{
	private:
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec4 RGBA;

	public:
		float duration;

		Particle(glm::vec2 position, glm::vec2 velocity, glm::vec4 RGBA, float duration);

		void Update(const float& dt);

		void Draw();
};

class ParticleEmitter
{
	private:
		const glm::vec2 position;
		const float particleDuration;
		const int emitRate;
		const float emitInterval;
		float emitDuration;
		int aliveParticles;
		Particle* particleList[1000000];

	public:
		ParticleEmitter(const glm::vec2& position, const float& particleDuration, const int& emitRate, const float& emitInterval);

		void Update(const float& dt);
		void AddParticles();
};

#endif