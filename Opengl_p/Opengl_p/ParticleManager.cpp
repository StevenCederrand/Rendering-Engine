#include "ParticleManager.h"
#include <cstdlib>

ParticleManager::ParticleManager()
{
	this->numberOfParticles = 0;
	float sizeOfAnParticle = 0.15f;
	vertex_buffer_data[0] = -sizeOfAnParticle;
	vertex_buffer_data[1] = -sizeOfAnParticle;
	vertex_buffer_data[2] = 0.0f;

	vertex_buffer_data[3] = sizeOfAnParticle;
	vertex_buffer_data[4] = -sizeOfAnParticle;
	vertex_buffer_data[5] = 0.0f;

	vertex_buffer_data[6] = -sizeOfAnParticle;
	vertex_buffer_data[7] = sizeOfAnParticle;
	vertex_buffer_data[8] = 0.0f;

	vertex_buffer_data[9] = sizeOfAnParticle;
	vertex_buffer_data[10] = sizeOfAnParticle;
	vertex_buffer_data[11] = 0.0f;

	/*for (size_t i = 0; i < PARTICLES_MAX; i++) {
		particles.emplace_back(Particle());
	}*/

	this->setupBuffers();
}

ParticleManager::~ParticleManager()
{
	glDeleteBuffers(1, &verticesVBO);
	glDeleteBuffers(1, &positionCenterVBO);
	glDeleteBuffers(1, &colourVBO);
	glDeleteVertexArrays(1, &VAO);
}

void ParticleManager::update()
{

	positionBuffer.clear();
	colourBuffer.clear();
	for (int i = 0; i < this->numberOfParticles; i++)
	{
		particles.at(i).updateLife();

		if (!particles.at(i).remainingTime())
		{
			this->numberOfParticles--;
			continue;
		}
		particles.at(i).update();


		positionBuffer.emplace_back(particles.at(i).getPosition());
		colourBuffer.emplace_back(particles.at(i).getColor());

	}

	updateBuffers();

}

int ParticleManager::getNumberOfParticles()
{
	return this->numberOfParticles;
}

void ParticleManager::addParticles(const glm::vec3 & pos, const glm::vec3 & velocity, int particlesNumber)
{
	for (int i = 0; i < particlesNumber; i++)
	{
		if (this->numberOfParticles == PARTICLES_MAX)
			return;
		
		//give the pos and the velocity a little change
		glm::vec3 newPos = pos;
		newPos.x += (rand() % 2) / 2.0f;
		newPos.y += (rand() % 2) / 2.0f;
		newPos.z += (rand() % 2) / 2.0f;

		glm::vec3 newVel = velocity;
		newVel.x += (rand() % 2) / 10.0f;
		newVel.z += (rand() % 2) / 10.0f;
	
		Particle p(newPos, newVel);

		//find if there is a particle in the vector
		//that is not used and use that
		int unUsed = findUnusedParticle();
		if (unUsed != -1)
		{
			this->particles.at(unUsed).renewParticle(p);
		}
		//or send the particle to the back of the vector
		else 
		{
			particles.emplace_back(p);

		}
		this->numberOfParticles++;

	}
}

unsigned int ParticleManager::getVAO()
{
	return this->VAO;
}
//return the UnusedParticle position in the vector
int ParticleManager::findUnusedParticle()
{
	for (int i = 0; i < this->particles.size(); i++)
	{
		if (!(this->particles.at(i).remainingTime()))
		{
			return i;

		}
	}
	return -1;
}

void ParticleManager::setupBuffers()
{
	glGenVertexArrays(1, &this->VAO);

	glGenBuffers(1, &verticesVBO);
	glGenBuffers(1, &positionCenterVBO);
	glGenBuffers(1, &colourVBO);

	glBindVertexArray(this->VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);


	// Buffer for Positions center
	glBindBuffer(GL_ARRAY_BUFFER, positionCenterVBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLES_MAX * sizeof(glm::vec3), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glVertexAttribDivisor(1, 1);

	// Buffer for color
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLES_MAX * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glVertexAttribDivisor(2, 1);


	glBindVertexArray(NULL);

}

void ParticleManager::updateBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, positionCenterVBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLES_MAX * sizeof(glm::vec3), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, positionBuffer.size() * sizeof(glm::vec3), positionBuffer.data());

	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLES_MAX * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, colourBuffer.size() * sizeof(glm::vec4), colourBuffer.data());

	glBindBuffer(GL_ARRAY_BUFFER, NULL);


}
