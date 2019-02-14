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

		glDrawArrays(GL_TRIANGLES, 0, objects.at(i).getMesh().verts.size());
		objloader.unbindVAO();
		objloader.unbindVBO();
	}


}

void Renderer::clearBuffers() {
	glClearColor(0.1f, 0.1f, 0.1f, 1);

	//Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
