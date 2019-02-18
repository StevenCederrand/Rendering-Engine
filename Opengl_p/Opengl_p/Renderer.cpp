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

void Renderer::render(ObjectLoader objloader, std::vector<Object> objects, Shader* shader) {
	this->clearBuffers();
	
	//Itterate through every object
	for (int i = 0; i < objects.size(); i++) {
		objloader.bindVAO(i);
		objloader.bindVBO(i);

		if (objects.at(i).type == ObjectTypes::LightSource) {
			shader->setVec3("lightPos", objects.at(i).position);
			shader->setInt("type", 2);
		}
		else if (objects.at(i).type == ObjectTypes::HeightMapBased) {
			shader->setInt("type", 1);
		}
		else if (objects.at(i).type == ObjectTypes::Standard) {
			shader->setInt("type", 0);
		}
		if (objects.at(i).name == "L2") {
			objects.at(i).modelMatrix = glm::translate(glm::vec3(10, 5, 10));
			objects.at(i).position = glm::vec3(10, 5, 10);
			shader->setVec3("lightPos", objects.at(i).position);
		}
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
