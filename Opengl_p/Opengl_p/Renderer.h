#ifndef RENDERER_h
#define RENDERER_h
#include "ObjectLoader.h"
#include "ObjectManager.h"
class Renderer {
public:
	Renderer();
	Renderer(int width, int height);
	~Renderer();

	void render(ObjectLoader *objloader, std::vector<Object> objects);
	void render(ObjectLoader objloader, ObjectManager *objManager, Shader* shader);
	void render(ObjectLoader objloader, std::vector<Object> objects, Shader* shader);

	void start();
	void setupLightPassShader(Shader* lighPassShader);
	void clearBuffers();
	int lightCount = 0;

private:
	void bindBufferTextures();


private: 
	GLuint gBuffer;
	GLuint gNormal;
	GLuint gPosition;
	GLuint gColorSpecular;

	//Depth buffer
	GLuint rboDepth; //Rename this
	GLuint colAttachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	int scrWidth;
	int scrHeight;
	std::string getNextLight();
};


#endif