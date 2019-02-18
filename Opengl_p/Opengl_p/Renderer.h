#ifndef RENDERER_h
#define RENDERER_h
#include "ObjectLoader.h"
#include "ObjectManager.h"
class Renderer {
public:
	Renderer();
	~Renderer();

	void render(ObjectLoader *objloader, std::vector<Object> objects);
	void render(ObjectLoader objloader, ObjectManager *objManager, Shader* shader);
	void render(ObjectLoader objloader, std::vector<Object> objects, Shader* shader);

	void start();
	void clearBuffers();
	int lightCount = 0;

private: 

	std::string getNextLight();
};


#endif