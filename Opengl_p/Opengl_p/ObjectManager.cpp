#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	this->fileloader = new Fileloader();
}

ObjectManager::~ObjectManager() {
	delete this->fileloader;
}

void ObjectManager::start() {

}

std::vector<Object> ObjectManager::getObjects() {
	return this->objects;
}

std::vector<Object>& ObjectManager::handleObjects() {
	return this->objects;
}


void ObjectManager::readFromFile(std::string filename, std::string objName, ObjectTypes objectType, Shader* shader) {
	
	Object obj;
	shader->use();

	if (objectType == ObjectTypes::HeightMapBased) {
		obj = fileloader->loadMap(OBJECTSPATH + filename);
	}
	else if(objectType == ObjectTypes::Standard){
		obj = fileloader->readFile(OBJECTSPATH + filename);
		obj.setPosition(this->position);
		position.x += 10;
	}
	else {
		obj = fileloader->readFile(OBJECTSPATH + filename);
	}
	obj.type = objectType;
	obj.init();

	if (objectType == ObjectTypes::LightSource) {
		obj.setPosition(glm::vec3(0, 10, 0));
		
		obj.pointLight = new PointLight();
		obj.pointLight->factors = glm::vec4(1.0f, 0.09f, 0.032f, 0.1f);

		this->lightcount++;
	}
	if (objName == "L1") {
		obj.setPosition(glm::vec3(45, 3, 10));
	}
	obj.name = objName;
	this->objects.push_back(obj);
}

float ObjectManager::getElevation(glm::vec3 position)
{
	return fileloader->getElevation(position);
}

int ObjectManager::getLightCount() const
{
	return this->lightcount;
}

void ObjectManager::destroyLight(int at) {
	this->objects.at(at).destroyLight();
}

