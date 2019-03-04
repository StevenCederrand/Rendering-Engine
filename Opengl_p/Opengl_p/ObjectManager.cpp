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


void ObjectManager::readFromFile(std::string filename, std::string objName, ObjectTypes objectType, Shader* shader) {
	
	Object obj;
	shader->use();

	if (objectType == ObjectTypes::HeightMapBased) {
		obj = fileloader->loadMap(OBJECTSPATH + filename);
	}
	else {
		obj = fileloader->readFile(OBJECTSPATH + filename);
	}
	obj.type = objectType;
	this->objectloader->loadObject(obj, shader);

	if (objectType == ObjectTypes::LightSource) {
		obj.position = glm::vec3(0, 10, 0);
		obj.modelMatrix = glm::translate(obj.position);
		obj.pointLight = new PointLight();
		obj.pointLight->constant = 1.0f;
		obj.pointLight->linear = 0.09f;
		obj.pointLight->quadratic = 0.032f;
		this->lightcount++;
	}
	obj.name = objName;
	this->objects.push_back(obj);
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

int ObjectManager::getLightCount() const
{
	return this->lightcount;
}

void ObjectManager::destroyLight(int at) {
	this->objects.at(at).destroyLight();
}

