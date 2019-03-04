#include "Renderer.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {
	glDeleteFramebuffers(1, &this->FBO);
}

void Renderer::start(int scrX, int scrY) {
	this->scrX = scrX;
	this->scrY = scrY;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	

	glGenFramebuffers(1, &this->FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);

	glGenTextures(1, &this->positionBuffer);
	glBindTexture(GL_TEXTURE_2D, this->positionBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scrX, scrY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->positionBuffer, 0);
	
	glGenTextures(1, &this->normalBuffer);
	glBindTexture(GL_TEXTURE_2D, this->normalBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scrX, scrY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->normalBuffer, 0);

	glGenTextures(1, &this->colourBuffer);
	glBindTexture(GL_TEXTURE_2D, this->colourBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, scrX, scrY, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
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

void Renderer::render(ObjectLoader *objloader, std::vector<Object> objects) {
	this->clearBuffers();
	std::cout << objects.size() << std::endl;

	int step = 0;
	//Itterate through every object
	for (int i = 0; i < objects.size(); i++) {
		objloader->bindVAO(i);
		objloader->bindVBO(i);
		
		glDrawArrays(GL_TRIANGLES, step, objects.at(i).getMesh().verts.size());

		step = objects.at(i).getMesh().verts.size();
		objloader->unbindVAO();
		objloader->unbindVBO();
	}
}

void Renderer::render(ObjectLoader objloader, ObjectManager *objManager, Shader *shader) {

	this->clearBuffers();

	//Itterate through every object
	for (int i = 0; i < objManager->getObjects().size(); i++) {
		objloader.bindVAO(i);
		objloader.bindVBO(i);

		if (objManager->getObjects().at(i).type == ObjectTypes::LightSource) {
			//std::cout << this->getNextLight() << std::endl;


			shader->setVec3("pointLights[0].lPos", objManager->getObjects().at(i).position);
			shader->setFloat("pointLights[0].lConstant", objManager->getObjects().at(i).pointLight->constant);
			shader->setFloat("pointLights[0].lLinear", objManager->getObjects().at(i).pointLight->linear);
			shader->setFloat("pointLights[0].lQuadratic", objManager->getObjects().at(i).pointLight->quadratic);

			shader->setVec3("pointLights[1].lPos", objManager->getObjects().at(i).position);
			shader->setFloat("pointLights[1].lConstant", objManager->getObjects().at(i).pointLight->constant);
			shader->setFloat("pointLights[1].lLinear", objManager->getObjects().at(i).pointLight->linear);
			shader->setFloat("pointLights[1].lQuadratic", objManager->getObjects().at(i).pointLight->quadratic);
			shader->setInt("type", 2);
		}
		else if (objManager->getObjects().at(i).type == ObjectTypes::HeightMapBased) {
			shader->setInt("type", 1);
		}
		else if (objManager->getObjects().at(i).type == ObjectTypes::Standard) {
			shader->setInt("type", 0);
		}
		if (objManager->getObjects().at(i).name == "L2") {
			objManager->getObjects().at(i).position = glm::vec3(10, 3, 10);

			objManager->getObjects().at(i).modelMatrix = glm::translate(objManager->getObjects().at(i).position);
			shader->setVec3("lightPos", objManager->getObjects().at(i).position);
		}
		//shader->setInt("lights", 2);
		shader->setMat4("worldMatrix", objManager->getObjects().at(i).modelMatrix);

		glDrawArrays(GL_TRIANGLES, 0, objManager->getObjects().at(i).getMesh().verts.size());

		objloader.unbindVAO();
		objloader.unbindVBO();
	}
}

void Renderer::render(ObjectLoader objloader, std::vector<Object> objects, Shader* shader) {
	//Use the framebuffer that we created
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
	glEnable(GL_DEPTH_TEST);

	this->clearBuffers();
	shader->use();

	objloader.bindVAO(0);
	objloader.bindVBO(0);
	if (objects.at(0).type == ObjectTypes::HeightMapBased) {
		shader->setInt("type", 1);
	}
	else if (objects.at(0).type == ObjectTypes::Standard) {
		shader->setInt("type", 0);
	}
	shader->setMat4("worldMatrix", objects.at(0).modelMatrix);

	glDrawArrays(GL_TRIANGLES, 0, objects.at(0).getMesh().verts.size());
	objloader.unbindVAO();
	objloader.unbindVBO();

	/*
	//Itterate through every object
	for (int i = 0; i < objects.size(); i++) {
		objloader.bindVAO(i);
		objloader.bindVBO(i);

		if (objects.at(i).name == "L2") {
			objects.at(i).position = glm::vec3(45, 3, 10);

			objects.at(i).modelMatrix = glm::translate(objects.at(i).position);
			shader->setVec3("lightPos", objects.at(i).position);

			shader->setVec3("pointLights[1].lPos", objects.at(i).position);
			shader->setFloat("pointLights[1].lConstant", objects.at(i).pointLight->constant);
			shader->setFloat("pointLights[1].lLinear", objects.at(i).pointLight->linear);
			shader->setFloat("pointLights[1].lQuadratic", objects.at(i).pointLight->quadratic);

		}

		if (objects.at(i).name == "L1") {
			//std::cout << this->getNextLight() << std::endl;
			shader->setVec3("pointLights[0].lPos", objects.at(i).position);
			shader->setFloat("pointLights[0].lConstant", objects.at(i).pointLight->constant);
			shader->setFloat("pointLights[0].lLinear", objects.at(i).pointLight->linear);
			shader->setFloat("pointLights[0].lQuadratic", objects.at(i).pointLight->quadratic);

			lightCount++; //Problem here

			shader->setInt("type", 2);
		}
		else if (objects.at(i).type == ObjectTypes::HeightMapBased) {
			shader->setInt("type", 1);
		}
		else if (objects.at(i).type == ObjectTypes::Standard) {
			shader->setInt("type", 0);
		}

		//shader->setInt("lights", 2);
		shader->setMat4("worldMatrix", objects.at(i).modelMatrix);

		glDrawArrays(GL_TRIANGLES, 0, objects.at(i).getMesh().verts.size());
		objloader.unbindVAO();
		objloader.unbindVBO();
	}*/
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::deferredRender(ObjectLoader objloader, std::vector<Object> objects, ShaderManager* shaderManager) {
	//Geometry Pass
	//Use the framebuffer that we created
	this->geometryPass(objloader, objects, shaderManager->getSpecific("GeometryPass"));

	//LightPass
	this->lightPass(objects, shaderManager->getSpecific("LightPass"));
}


void Renderer::geometryPass(ObjectLoader objloader, std::vector<Object> objects, Shader* geometryPass) {
	geometryPass->use();
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
	glEnable(GL_DEPTH_TEST);

	this->clearBuffers();

	for (int i = 0; i < objects.size(); i++) {
		ObjectTypes type = objects.at(i).type;
		if (type != ObjectTypes::LightSource) {
			objloader.bindVAO(i);
			objloader.bindVBO(i);

			if (type == ObjectTypes::HeightMapBased) {
				geometryPass->setInt("type", 1);
			}
			else if (type == ObjectTypes::Standard) {
				geometryPass->setInt("type", 0);
			}
			geometryPass->setMat4("worldMatrix", objects.at(i).modelMatrix);

			glDrawArrays(GL_TRIANGLES, 0, objects.at(i).getMesh().verts.size());
			objloader.unbindVAO();
			objloader.unbindVBO();
		}
		
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::lightPass(std::vector<Object> objects, Shader* lightPass) {
	lightPass->use();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT);
	//Loop through all of the lights in the scene
	for (int i = 0; i < objects.size(); i++) {
		if (objects.at(i).type == ObjectTypes::LightSource) {
			if (objects.at(i).name == "L1") {
				objects.at(i).position = glm::vec3(45, 3, 10);
				objects.at(i).modelMatrix = glm::translate(objects.at(i).position);

				lightPass->setVec3("pointLights[0].position", objects.at(i).position);
				lightPass->setFloat("pointLights[0].constant", objects.at(i).pointLight->constant);
				lightPass->setFloat("pointLights[0].linear", objects.at(i).pointLight->linear);
				lightPass->setFloat("pointLights[0].quadratic", objects.at(i).pointLight->quadratic);
			}

			if (objects.at(i).name == "L2") {
				lightPass->setVec3("pointLights[1].position", objects.at(i).position);
				lightPass->setFloat("pointLights[1].constant", objects.at(i).pointLight->constant);
				lightPass->setFloat("pointLights[1].linear", objects.at(i).pointLight->linear);
				lightPass->setFloat("pointLights[1].quadratic", objects.at(i).pointLight->quadratic);

			}
		}
	}

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