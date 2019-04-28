#ifndef OBJECTMANAGER_h
#define OBJECTMANAGER_h

#include "Object.h"
#include "Fileloader.h"
#include "Shader.h"

class ObjectManager {
public:
	ObjectManager();

	~ObjectManager();

	std::vector<Object> getObjects();
	std::vector<Object>& handleObjects();//be careful using this!
	
	void start();
	//Read files -> input the type of object
	void readFromFile(std::string filename, std::string objName, ObjectTypes objectType, Shader* shader);
	float getElevation(glm::vec3 position);
	int getLightCount() const;
	void destroyLight(int at);

private:
	std::vector<Object> objects;
	Fileloader* fileloader;
	int lightcount = 0;
	glm::vec3 position = glm::vec3(10, 2, 10);

};


#endif