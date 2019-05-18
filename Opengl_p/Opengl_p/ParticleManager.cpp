#include "ParticleManager.h"


ParticleManager::ParticleManager()
{
	this->numberOfParticles = 0;
	float sizeOfAnParticle = 5.0f;
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
	this->setupBuffers();
}

ParticleManager::~ParticleManager()
{
	glDeleteBuffers(1, &verticesVBO);
	glDeleteBuffers(1, &positionVBO);
	glDeleteBuffers(1, &colourVBO);
	glDeleteVertexArrays(1, &VAO);
}

void ParticleManager::update()
{
	positionBuffer.clear();
	colourBuffer.clear();
	for (int i = 0; i < particles.size(); i++)
	{
		if (!particles.at(i).remainingTime()) {
			this->numberOfParticles--;
			continue;
		}

		particles.at(i).updateLife();

		if (!particles.at(i).remainingTime())
		{
			this->numberOfParticles--;
			continue;
		}
		particles.at(i).update();


		positionBuffer.emplace_back(particles.at(i).getVel());
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
		
		glm::vec3 newPos = pos;
		newPos.x += i;
		newPos.y += i;
		newPos.z += i;
		Particle p(newPos, velocity);

		particles.emplace_back(p);
		this->numberOfParticles++;

	}
}

unsigned int ParticleManager::getVAO()
{
	return this->VAO;
}

void ParticleManager::setupBuffers()
{
	glGenVertexArrays(1, &this->VAO);

	glGenBuffers(1, &verticesVBO);
	glGenBuffers(1, &positionVBO);
	glGenBuffers(1, &colourVBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, 12, vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);


	// Buffer for centerPositions
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLES_MAX * sizeof(glm::vec3), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glVertexAttribDivisor(1, 1);

	// Buffer for color
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLES_MAX * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glVertexAttribDivisor(2, 1);


	glBindVertexArray(NULL);

}

void ParticleManager::updateBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLES_MAX * sizeof(glm::vec3), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, positionBuffer.size() * sizeof(glm::vec3), positionBuffer.data());

	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLES_MAX * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, colourBuffer.size() * sizeof(glm::vec4), colourBuffer.data());

	glBindBuffer(GL_ARRAY_BUFFER, NULL);


}
