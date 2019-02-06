#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	this->loader = new Fileloader();
}

ObjectManager::~ObjectManager() {
	delete loader;
}

std::vector<Object> ObjectManager::getObjects() const {
	return this->objects;
}

void ObjectManager::loadObject(std::string filename) {
	Object obj = loader->readFile(OBJECTSPATH + filename);
	this->objects.push_back(obj);
}

void ObjectManager::loadObject(std::string path, std::string name) {
	Object obj = loader->readFile(path + name);
	this->objects.push_back(obj);
}

void ObjectManager::loadMap(std::string path)
{
//	Object obj = loader->loadMap(OBJECTSPATH+path, );
//	this->objects.push_back(obj);
}

void ObjectManager::setupObjects(Shader * shader) {

	GLint attributeLocation = 0;
	if (attributeLocation == -1) {
		std::cout << "ERROR::LOCATING::VERTEX::POS" << std::endl;
		return;
	}

	//Set the vertices in the glsl-code
	glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	//Load normals
	attributeLocation = 1;
	if (attributeLocation == -1) {
		std::cout << "ERROR::LOCATING::NORMAL::POS" << std::endl;
		return;
	}
	glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(glm::vec3)));
	glEnableVertexAttribArray(attributeLocation);

	//Load uv's
	attributeLocation = 2;
	if (attributeLocation == -1) {
		std::cout << "ERROR::LOCATING::UV::POS" << std::endl;
		return;
	}
	glVertexAttribPointer(attributeLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(float) * 6));
	glEnableVertexAttribArray(attributeLocation);
}
