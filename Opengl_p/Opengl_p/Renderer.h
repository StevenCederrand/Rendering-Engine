#ifndef RENDERER_h
#define RENDERER_h

#include "ObjectLoader.h"
#include "ObjectManager.h"
#include "ShaderManager.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void render(std::vector<Object> objects, Shader* shader, unsigned int depthFramebuffer);
	void deferredRender(std::vector<Object> objects, 
		ShaderManager* shaderManager,
		unsigned int depthMap);

	void start(int x, int y);
	void clearBuffers();
	void clear();


private:
	void initRenderQuad();
	void geometryPass(std::vector<Object> objects, Shader* geometryPass);
	void lightPass(std::vector<Object> objects, Shader* lightPass);
	void bindTextures(Shader* lightPass);
	
private: 
	//Variables associated with deferred rendering

#pragma region Deferred rendering
	unsigned int FBO;
	unsigned int RBO;

	unsigned int positionBuffer;
	unsigned int normalBuffer;
	unsigned int colourBuffer;
	unsigned int depthMap;

	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};	
	
	unsigned int rQuadVAO;
	unsigned int rQUadVBO;

	float rQuadData[24] = {
		//VP			UV
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
#pragma endregion

	int scrX;
	int scrY;

};


#endif