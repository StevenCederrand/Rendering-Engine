#include "Renderer.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {

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
			/*
			shader->setVec3(this->getNextLight() + ".lPos", objManager->getObjects().at(i).position);
			shader->setFloat(this->getNextLight() + ".lConstant", objManager->getObjects().at(i).pointLight->constant);
			shader->setFloat(this->getNextLight() + ".lLinear", objManager->getObjects().at(i).pointLight->linear);
			shader->setFloat(this->getNextLight() + ".lQuadratic", objManager->getObjects().at(i).pointLight->quadratic);
			*/
			/*if (this->lightCount < objManager->getLightCount()) {
				lightCount++; //Problem here
			}*/

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
	this->clearBuffers();
	
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
	}
}

void Renderer::start() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::clearBuffers() {
	glClearColor(0.1f, 0.1f, 0.1f, 1);

	//Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

std::string Renderer::getNextLight() {
	std::string name = "pointLights[";
	name += std::to_string(lightCount);
	name += "]";
	return name;
}