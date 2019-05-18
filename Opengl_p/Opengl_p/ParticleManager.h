#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
#include "Particle.h"
#include "Containers.h"
#include "Shader.h"

#define PARTICLES_MAX 50
class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();
	void update();

	int getNumberOfParticles();
	void addParticles(const glm::vec3& pos, const glm::vec3& velocity, int numberOfParticles);
	unsigned int getVAO();
private:
	
	std::vector<Particle> particles;
	std::vector<glm::vec3> positionBuffer;
	std::vector<glm::vec4> colourBuffer;

	int numberOfParticles;
	unsigned int VAO;

	unsigned int verticesVBO;
	unsigned int positionVBO;
	unsigned int colourVBO;

	//Mesh mesh;
	float vertex_buffer_data[12];

private:
	void setupBuffers();
	void updateBuffers();
	

};





#endif // !PARTICLEMANAGER_H

