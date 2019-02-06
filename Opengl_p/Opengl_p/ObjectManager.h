#ifndef OBJECTMANAGER_h
#define OBJECTMANAGER_h

#include "Object.h"
#include "Fileloader.h"
#include "Shader.h"

class ObjectManager {
public:
	ObjectManager();

	~ObjectManager();

	std::vector<Object> getObjects() const;
	//Load an object by filename
	void loadObject(std::string filename);
	void loadObject(std::string path, std::string name);
	void loadMap(std::string path);

	void setupObjects(Shader* shader);

private:
	std::vector<Object> objects;
	Fileloader* loader;
};


#endif