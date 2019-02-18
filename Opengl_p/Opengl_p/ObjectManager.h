#ifndef OBJECTMANAGER_h
#define OBJECTMANAGER_h

#include "Object.h"
#include "ObjectLoader.h"
#include "Fileloader.h"
#include "Shader.h"

class ObjectManager {
public:
	ObjectManager();

	~ObjectManager();

	std::vector<Object> getObjects() const;
	
	void start();
	//Read files -> input the type of object
	void readFromFile(std::string filename, std::string objName, ObjectTypes objectType, Shader* shader);
	void destroy();
	float getElevation(glm::vec3 position);
	ObjectLoader getObjectloader();
	int getLightCount() const;

private:
	std::vector<Object> objects;
	Fileloader* fileloader;
	ObjectLoader* objectloader; //Contains VBOs, VAOs etc. I,e data for rendering 
	int lightcount = 0;
};


#endif