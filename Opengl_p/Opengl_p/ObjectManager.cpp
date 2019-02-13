#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	this->fileloader = new Fileloader();
	this->objectloader = new ObjectLoader();

}

ObjectManager::~ObjectManager() {
	delete this->fileloader;
	delete this->objectloader;
}

void ObjectManager::start() {

}

std::vector<Object> ObjectManager::getObjects() const {
	return this->objects;
}


void ObjectManager::readFromFile(std::string filename, int objectType, Shader* shader) {
	
	if (objectType == ObjectTypes::Standard) {
		shader->use();
		Object obj = fileloader->readFile(OBJECTSPATH + filename);
		this->objectloader->loadObject(obj, shader);
		this->objects.push_back(obj);
	}
	else if (objectType == ObjectTypes::HeightMapBased) {
		shader->use();
		Object obj = fileloader->loadMap(OBJECTSPATH + filename);
		this->objectloader->loadObject(obj, shader);
		this->objects.push_back(obj);
	}
	else {
		std::cout << "WARNING::OBJECT::NOT::SUPPORTED" << std::endl;
		return;
	}
}

void ObjectManager::readFromFile(std::string path, std::string filename, int objectType, Shader* shader) {

	if (objectType == ObjectTypes::Standard) {
		Object obj = fileloader->readFile(path + filename);
		this->objectloader->loadObject(obj, shader);
		this->objects.push_back(obj);
	}
	else if (objectType == ObjectTypes::HeightMapBased) {
		Object obj = fileloader->loadMap(path + filename);
		this->objectloader->loadObject(obj, shader);
		this->objects.push_back(obj);
	}
	else {
		std::cout << "WARNING::OBJECT::NOT::SUPPORTED" << std::endl;
		return;
	}
}

void ObjectManager::destroy() {
	this->objectloader->clean();
}

float ObjectManager::getElevation(glm::vec3 position)
{
	return fileloader->getElevation(position);
}

ObjectLoader  ObjectManager::getObjectloader() {
	return *this->objectloader;
}

