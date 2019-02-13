#ifndef RENDERER_h
#define RENDERER_h
#include "ObjectLoader.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void render(ObjectLoader *objloader, std::vector<Object> objects);
	void render(ObjectLoader objloader, std::vector<Object> objects, Shader* shader);

	void clearBuffers();
};


#endif