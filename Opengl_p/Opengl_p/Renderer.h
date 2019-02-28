#ifndef RENDERER_h
#define RENDERER_h
#include "ObjectLoader.h"
#include "ObjectManager.h"
#include "ShaderManager.h"
class Renderer {
public:
	Renderer();
	Renderer(int width, int height);
	~Renderer();

	void render(ObjectLoader *objloader, std::vector<Object> objects);
	void render(ObjectLoader objloader, ObjectManager *objManager, Shader* shader);
	void render(ObjectLoader objloader, std::vector<Object> objects, Shader* shader);
	void render(ObjectLoader objLoader, std::vector<Object> objects, ShaderManager* shaderManager);


	void geometryPass(ObjectLoader objLoader, std::vector<Object> objects, Shader* geometryPass);
	void lightPass(ObjectLoader objLoader, std::vector<Object> objects, Shader* lightPass);

	void start();
	void setLightCount(int lights);
	void setupLightPassShader(Shader* lightPassShader);
	void clearBuffers();


private:
	void bindBufferTextures();
	void renderQuad(); //Render the quad infront of the camera

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
	int lightCount = 0;
	std::string getNextLight();
	

	GLuint quadVAO;
	GLuint quadVBO;

	float quadVertices[24] = {
		-1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  -1.0f, 1.0f, 1.0f,

		 1.0f,  -1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f, 1.0f,
		 -1.0f, 1.0f, 0.0f, 1.0f,
	};

};


#endif