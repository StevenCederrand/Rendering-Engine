
/*
	This class is ideelly used as the bridge between the dirty code and the clean code. 
	-Steven Cederrand
*/
#ifndef APPLICATION_h
#define APPLICATION_h


#pragma region Local_Includes
#include "WND.h" //GLFW handler
#include "Containers.h"
#include "Fileloader.h"
#include "Object.h"
#include "Camera.h"
#include "Object.h"	//Contains basic 3D object class
#include "Shader.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "Deltatime.h"
#include "Acceleration.h"
#pragma endregion

#pragma region Default_Includes 
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include "stb_image.h"
#pragma endregion



//Files that may generate memory leaks - Application, WND, Object
class Application {

//Public functions
public:
	Application();
	Application(int WNDW, int WNDH);
	~Application();
		
	void setupShaders();
	void update();
	void render();
	void cameraHandler(Shader* shader);	
	
//Private functions
private:
	void start(); //Exists to reduce duplication
	void loadObjects();

	void depthMapFunction(unsigned int depthWidth, unsigned int depthHeight, unsigned int &depthMap, unsigned int &depthFramebuffer);

	void end();

	
//Private data
private:
	
	WND* window;
	Camera* camera;
	Fileloader fileloader;

	//the world matrix is used as a modelmatrix
	glm::mat4 worldMatrix = glm::mat4(1.f);
	glm::mat4 prjMatrix = glm::mat4(1.f);


	ValidKeys currentKey;
	Renderer renderer;
	ObjectManager* objectManager;
	Deltatime* deltaTime;
	ShaderManager *shaderManager;
	Acceleration *acceleration;
	double deltaT;
	unsigned int depthMap;
};
#endif