
/*
	This class is ideelly used as the bridge between the dirty code and the clean code. 
	-Steven Cederrand
*/
#ifndef APPLICATION_h
#define APPLICATION_h

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

#pragma region Local_Includes
#include "WND.h" //GLFW handler
#include "Containers.h"
#include "Fileloader.h"
#include "Object.h"
#include "Camera.h"
#include "Object.h"	//Contains basic 3D object class
#include "Shader.h"
#pragma endregion

#pragma region Default_Includes 
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#pragma endregion


//Files that may generate memory leaks - Application, WND, Object
class Application {

//Public functions
public:
	Application();
	Application(int WNDW, int WNDH);
	~Application();

	#pragma region SETUP FUNCTIONS
	void setupShaders();
	void setupObjects();
	void setupGround(); //change name
	void setupTextures();
	#pragma endregion
		
	void update();
	void render();
	void cameraHandler();	
	
//Private functions
private:
	void start(); //Exists to reduce duplication
	void loadObjects();
	void setColours();
	
//Private data
private:
	WND* window;
	Camera* camera;
	Shader* shader;
	Fileloader fileloader;

	GLuint vertexAttrib = 0;
	GLuint vertexBuffer = 0;
	GLuint normalBuffer = 0;


	//the world matrix is used as a modelmatrix
	glm::mat4 worldMatrix = glm::mat4(1.f);
	glm::mat4 prjMatrix = glm::mat4(1.f);

	Rotations rotations;
	ValidKeys currentKey;

	std::vector<Object> objs;
	int nrOfObjects = 0;

	std::vector<Object> objMap;
};
#endif