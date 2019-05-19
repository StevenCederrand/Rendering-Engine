#include "Particle.h"

Particle::Particle()
{
	this->time = 0.0f;
}

Particle::Particle(glm::vec3 position, glm::vec3 velocity)
{
	this->position = position;
	this->velocity = velocity;
	this->color = glm::vec4(1.0f);
	//this->rotation = rotation;
	this->time = TIMELIFE;

}

Particle::~Particle()
{
}

void Particle::update()
{
	this->position += this->velocity;
	this->color.a = this->time / TIMELIFE;
	//std::cout << this->color.a << std::endl;
}

void Particle::updateLife()
{
	this->time -= 0.2f;
	//std::cout << this->time << std::endl;
}

glm::vec3 Particle::getVel()
{
	return this->position;
}

glm::vec4 Particle::getColor()
{
	return this->color;
}

bool Particle::remainingTime()
{
	bool returnBool = false;
	if (this->time > 0)
	{
		returnBool = true;

	}
	return returnBool;
}

void Particle::renewParticle(Particle p)
{
	this->position = p.position;
	this->velocity = p.velocity;
	this->color = p.color;
	this->time = p.time;
	this->rotation = p.rotation;
}
