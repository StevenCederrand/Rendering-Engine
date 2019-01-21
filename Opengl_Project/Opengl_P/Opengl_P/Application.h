
/*
	This class is ideelly used as the bridge between the dirty code and the clean code. 
	-Steven Cederrand
*/
#ifndef APPLICATION_h
#define APPLICATION_h

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

#include "WND.h" //GLFW handler
#include "Containers.h"
#include "Object.h"	//Contains basic 3D object class

#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

class Application {

//Public functions
public:
	Application();
	Application(int WNDW, int WNDH);
	~Application();

	void setupShaders();
	void setupObjects();

	
	void update();
	void render();
	void rotate(float deltaTime);	
	
//Private functions
private:
	void start(); //Exists to reduce duplication

//Private data
private:
	WND* window;

	GLuint vertexAttrib = 0;
	GLuint vertexBuffer = 0;
	GLuint gShaderProg = 0;
	GLuint colorBuffer = 0;

	//the world matrix is used as a modelmatrix
	glm::mat4 worldMatrix = glm::mat4(1.f);
	glm::mat4 viewMatrix = glm::mat4(1.f);
	glm::mat4 prjMatrix = glm::mat4(1.f);

	Rotations rotations;
	ValidKeys currentKey;
	std::vector<Object> objs;

	float rotationVal = 0.05f;
	float xRotation = 0;
	float yRotation = 0;
	float zRotation = 0;

};
#endif