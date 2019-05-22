#include "Renderer.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {
	glDeleteFramebuffers(1, &this->FBO);
}

void Renderer::clear() {
	glDeleteTextures(1, &this->positionBuffer);
	glDeleteTextures(1, &this->normalBuffer);
	glDeleteTextures(1, &this->colourBuffer);
	glDeleteTextures(1, &this->depthMap);
	glDeleteFramebuffers(1, &this->FBO);

	glDeleteVertexArrays(1, &this->rQuadVAO);
	glDeleteBuffers(1, &this->rQUadVBO);

}

void Renderer::start(int scrX, int scrY) {
	this->scrX = scrX;
	this->scrY = scrY;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glGenFramebuffers(1, &this->FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);

	glGenTextures(1, &this->positionBuffer);
	glBindTexture(GL_TEXTURE_2D, this->positionBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, scrX, scrY, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->positionBuffer, 0);
	
	glGenTextures(1, &this->normalBuffer);
	glBindTexture(GL_TEXTURE_2D, this->normalBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, scrX, scrY, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->normalBuffer, 0);

	glGenTextures(1, &this->colourBuffer);
	glBindTexture(GL_TEXTURE_2D, this->colourBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, scrX, scrY, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, this->colourBuffer, 0);

	glDrawBuffers(3, attachments);

	glGenRenderbuffers(1, &this->RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scrX, scrY); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->RBO); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	this->initRenderQuad();
}

void Renderer::render(std::vector<Object> objects, Shader* shader, unsigned int depthFramebuffer) {
	//Use the framebuffer that we created
	shader->use();
	glBindFramebuffer(GL_FRAMEBUFFER, depthFramebuffer);
	glEnable(GL_DEPTH_TEST);

		
	for (size_t i = 0; i < objects.size(); i++) {
		ObjectTypes type = objects.at(i).type;

		if (type != ObjectTypes::LightSource) {
			
			shader->setMat4("worldMatrix", objects.at(i).modelMatrix);

			objects.at(i).draw(shader);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Renderer::deferredRender(std::vector<Object> objects, ShaderManager* shaderManager, unsigned int depthMap) {
	//Geometry Pass
	//Use the framebuffer that we created
	this->depthMap = depthMap;		
	this->geometryPass(objects, shaderManager->getSpecific("GeometryPass"));

	//LightPass
	this->lightPass(objects, shaderManager->getSpecific("LightPass"));
}

void Renderer::particlesRender(ParticleManager * particleManager, Shader * shader, glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	glEnable(GL_BLEND);
	shader->use();
	shader->setMat4("viewMatrix", viewMatrix);
	shader->setMat4("projectionMatrix", projMatrix);

	glBindVertexArray(particleManager->getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 12, particleManager->getNumberOfParticles());
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);

	glDisable(GL_BLEND);
}

void Renderer::geometryPass(std::vector<Object> objects, Shader* geometryPass) {
	geometryPass->use();
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
	glEnable(GL_DEPTH_TEST);

	this->clearBuffers();

	for (size_t i = 0; i < objects.size(); i++) {
		ObjectTypes type = objects.at(i).type;

		if (type != ObjectTypes::LightSource) {
			
			if (type == ObjectTypes::HeightMapBased) {
				geometryPass->setInt("type", 1);
			}
			else if (type == ObjectTypes::Standard) {
				geometryPass->setInt("type", 0);
				//if (objects.at(i).name == "RCube") {
				//	objects.at(i).setRotation(this->angle, glm::vec3(0, 1, 0));
				//	angle += 0.01f;
				//}
			}
				//objects.at(i).setRotation(this->angle, glm::vec3(0, 1, 0));
				//angle += 0.01f;
		} 
			geometryPass->setMat4("worldMatrix", objects.at(i).modelMatrix);

			objects.at(i).draw(geometryPass);
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::lightPass(std::vector<Object> objects, Shader* lightPass) {
	lightPass->use();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glClear(GL_COLOR_BUFFER_BIT);

	//Loop through all of the lights in the scene
	for (size_t i = 0; i < objects.size(); i++) {
		if (objects.at(i).type == ObjectTypes::LightSource) {

			if (objects.at(i).name == "L1") {
				glm::vec4 position = glm::vec4(objects.at(i).getPosition(), 0);
				lightPass->setVec4("pointLights[0].position", position);
				//Attenuation factors
				lightPass->setVec4("pointLights[0].factors", objects.at(i).pointLight->factors);
			}

			if (objects.at(i).name == "L2") {
				glm::vec4 position = glm::vec4(objects.at(i).getPosition(), 0);

				//lightPass->setVec3("pointLights[0].position", position);
				////Attenuation factors
				//lightPass->setVec4("pointLights[0].factors", objects.at(i).pointLight->factors);
			}
		}
	}

	glDisable(GL_DEPTH_TEST);
	//RenderQuad
	glBindVertexArray(this->rQuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->rQUadVBO);
	this->bindTextures(lightPass);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//Bind the textures created in the FBO
void Renderer::bindTextures(Shader* lightPass) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->positionBuffer);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->normalBuffer);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->colourBuffer);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, this->depthMap);
}

void Renderer::clearBuffers() {
	glClearColor(0.1f, 0.1f, 0.1f, 1);

	//Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//Configure render quad
void Renderer::initRenderQuad() {
	glGenVertexArrays(1, &this->rQuadVAO);
	glGenBuffers(1, &this->rQUadVBO);

	glBindVertexArray(this->rQuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->rQUadVBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(rQuadData), &rQuadData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));	
}

