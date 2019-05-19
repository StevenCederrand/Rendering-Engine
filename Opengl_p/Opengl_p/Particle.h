#ifndef PARTICLE_H
#define PARTICLE_H
#include "Containers.h"
#include <iostream>

#define TIMELIFE 10.0f
class Particle
{
public:
	Particle();
	Particle(glm::vec3 position, glm::vec3 velocity);
	~Particle();
	void update();
	void updateLife();


	glm::vec3 getPosition();
	glm::vec4 getColor();
	bool remainingTime();
	void renewParticle(Particle p);
private:

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 color;

	float time;


};



#endif // !PARTICLE_H

