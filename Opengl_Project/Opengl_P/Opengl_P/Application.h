
/*
	This class is ideelly used as the bridge between the dirty code and the clean code. 
	-Steven Cederrand
*/
#ifndef APPLICATION_h
#define APPLICATION_h

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

#include "WND.h" //GLFW handler
#include "Containers.h"
#include "Fileloader.h"
#include "Object.h"""

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
	void setupTriangle();

	
	void update();
	void render();
	void rotate(float deltaTime);	
	

	/*void setupOBJ();
	bool loadOBJ(std::string path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outUV, std::vector<glm::vec3>& outNormals);*/
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

	float rotationVal = 0.05f;
	float xRotation = 0;
	float yRotation = 0;
	float zRotation = 0;

	//For the object parser
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normals;
};
#endif