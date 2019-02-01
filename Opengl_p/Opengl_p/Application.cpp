#include "Application.h"

using ms = std::chrono::duration<float, std::milli>;

//Start(): 
//Creates a default window. 
Application::Application() {

	this->window = new WND();
	this->window->start();
}
//Start(): 
//Creates a window with a specific size
Application::Application(int WNDW, int WNDH) {

	this->window = new WND(WNDW, WNDH);
	this->window->start();
}

Application::~Application() {
	//Critical error when deleting this->window??
	delete this->window;
	delete this->shader;
	delete this->camera;

}
//Setup the matrixes
void Application::start() {

	//this->viewMatrix = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	this->camera = new Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), this->window->getWindow());

	this->prjMatrix = glm::perspective(glm::radians(65.0f), (float)this->window->getResolution().first / (float)this->window->getResolution().second, 0.1f, 20.0f);
	//Set World Matrix	
	this->shader->setMat4("worldMatrix", this->worldMatrix);
	//Set View Matrix
	this->shader->setMat4("viewMatrix", this->camera->getViewMatrix());
	//Set Projection Matrix
	this->shader->setMat4("prjMatrix", this->prjMatrix);



	this->currentKey = ValidKeys::DUMMY;	
}

void Application::setupShaders() {
	this->shader = new Shader(SHADERPATH + "vShader.glsl", SHADERPATH + "fShader.glsl");
}

void Application::setupObjects() {
	//Wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	this->loadObjects();

	//Load the vertices into memory
	glGenVertexArrays(1, &this->vertexAttrib);
	glBindVertexArray(this->vertexAttrib);
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

	std::vector<glm::vec3> vertices;

	
	for (int i = 0; i < this->objs.at(0).getMesh().vertex.size(); i++) {
		vertices.push_back(this->objs.at(0).getMesh().vertex.at(i));
	}

	int totalSize = this->objs.at(0).getMesh().vertex.size() * sizeof(glm::vec3);
	
	//Load all vertices

	/*
	for (int i = 0; i < this->objs.size(); i++) {
		for (int j = 0; j < this->objs.at(i).getOrderedVertices().size(); j++) {
			vertices.push_back(this->objs.at(i).getOrderedVertices().at(j).vertex);
		}
	}
	int totalSize = 0;
	for (int i = 0; i < this->objs.size(); i++) {
		totalSize += this->objs.at(i).getByteSize();
	}*/


	//Load vertices into the buffer
	glBufferData(GL_ARRAY_BUFFER, totalSize, &vertices[0], GL_STATIC_DRAW);
	//Assign where in memory the positions are located	
	GLint vertexPos = glGetAttribLocation(this->shader->getShaderID(), "position");
	if (vertexPos == -1) {
		std::cout << "Couldn't find vertexPos" << std::endl;
		return;
	}
	//Set the vertices in the glsl-code
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 0));
	glEnableVertexAttribArray(vertexPos);

	/*
	vertices.clear();
	//Load all vertices
	for (int i = 0; i < this->objs.size(); i++) {
		for (int j = 0; j < this->objs.at(i).getNormals().size(); j++) {
			vertices.push_back(this->objs.at(i).getNormals().at(j).vertex);
		}
	}

	totalSize = 0; 
	for (int i = 0; i < this->objs.size(); i++) {
		totalSize += this->objs.at(i).getSizeOfNormals();
	}
	glBufferData(GL_ARRAY_BUFFER, totalSize, &vertices[0], GL_STATIC_DRAW);*/

	/*
	GLint normalPos = glGetAttribLocation(this->shader->getShaderID(), "normal");
	if (normalPos == -1) {
		std::cout << "ERROR::LOCATING::NORMAL::POSITION" << std::endl;
		return;
	}

	//Set the vertices in the glsl-code
	glVertexAttribPointer(normalPos, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 0));
	glEnableVertexAttribArray(1);*/

	/*
	GLint normalPos = glGetAttribLocation(this->shader->getShaderID(), "normal");
	if (normalPos == -1) {
		std::cout << "ERROR::LOCATING::NORMAL_POS::IN::SHADER" << std::endl;
		return;
	}

	glVertexAttribPointer(normalPos, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 0));

	glEnableVertexAttribArray(0);
	*/

	
	this->shader->use();
	this->shader->setVec3("ambientCol", this->objs.at(0).getMaterial().ambientCol);
	this->shader->setVec3("diffuseCol", this->objs.at(0).getMaterial().diffuseCol);
}


void Application::setupGround()
{
	struct TriangleVertex{float x, y, z;};
	std::vector<float> elevation;
	int width = 0;
	int height = 0;
	fileloader.loadMap(OBJECTSPATH + "HeightMap.PNG", width, height, elevation);

	int size = width*height;
	int counter = 0;
	
	//create a trianglevertex struct of the size, width*height
	TriangleVertex *triangleVertices = new TriangleVertex[size];
	 //delete this senare
	for (size_t j = 0; j < height; j++)
	{
		for (size_t i = 0; i < width; i++)
		{
			int index = height * j + i;
			triangleVertices[index].x = (float)i;
			triangleVertices[index].y = elevation[counter] /15;//divide by a number so that it looks more "flat"
			triangleVertices[index].z = (float)j;
			counter++;
		}
	}
}


void Application::setupTextures() {
	//Texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	//Texture magnifying and minifying filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

//Runs every tick while the window is open
void Application::update() {

	this->setupShaders();
	this->setupObjects();
	this->setupGround();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Use the one shader that has been set up
	this->start();

	std::chrono::high_resolution_clock timer;

	auto frameTime = timer.now();
	auto stop = timer.now();

	double deltaTime = 0.0f;

	
	while (!glfwWindowShouldClose(this->window->getWindow())) {

		frameTime = timer.now();

		//Check input
		this->window->inputKey(this->currentKey);

		if (this->currentKey == ValidKeys::ESC) {
			glfwSetWindowShouldClose(this->window->getWindow(), true);
		}

		//Camera function 
		this->cameraHandler();
		
		//Render the VAO with the loaded shader
		this->render();
	
		stop = timer.now();
		//Deltatime in ms
		std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - frameTime;
		deltaTime = std::chrono::duration_cast<ms>(stop - frameTime).count() / 1000; 
		this->window->update();
	}
	
	this->window->close();
}

void Application::render() {
	glClearColor(0.1f, 0.1f, 0.1f, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	if (this->vertexAttrib != 0) {
		glBindVertexArray(this->vertexAttrib);
	}
	this->shader->use();

	//this->shader->setVec3("ambientCol", this->objs.at(0).getMaterial().ambientCol);
	//this->shader->setVec3("diffuseCol", this->objs.at(0).getMaterial().diffuseCol);

	int x = 0;
	//glDrawArrays(GL_TRIANGLES, x, this->objs.at(1).v.size() * 3 * sizeof(glm::vec3));
	/*
	for (int i = 0; i < this->objs.size(); i++) {
		this->shader->setVec3("ambientCol", this->objs.at(i).getMaterial().ambientCol);
		this->shader->setVec3("diffuseCol", this->objs.at(i).getMaterial().diffuseCol);
		glDrawArrays(GL_TRIANGLES, x, x + this->objs.at(i).getTriangles().size() * 3);
		x += this->objs.at(i).getTriangles().size() * 3;
	}	*/

	glDrawArrays(GL_TRIANGLES, 0, this->objs.at(0).getMesh().vertex.size() * 3);
}
//Have this be in an object class
void Application::cameraHandler() {

	this->camera->update();

	if (this->currentKey != ValidKeys::DUMMY) {
		camera->handleKeys(this->currentKey);
	}

	this->currentKey = ValidKeys::DUMMY;

	this->shader->setMat4("worldMatrix", this->worldMatrix);
	// This is so that we can "walk" with wasd keys
	this->shader->setMat4("viewMatrix", this->camera->getViewMatrix());
}

void Application::loadObjects() {

	//Observe the time it takes to load all of the objects
	std::chrono::high_resolution_clock timer;
	auto start = timer.now();

	//Insert all of the objects here!
	Object cube = this->fileloader.readFile(OBJECTSPATH + "Monkey.obj");
	Object cb = this->fileloader.loadObj(OBJECTSPATH + "Monkey.obj");


	auto end = timer.now();

	//Calculate the time it took to load
	std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - start;
	auto loadTime = std::chrono::duration_cast<ms>(end - start).count(); // in ms
	std::cout << "Loadtime(ms): " + std::to_string(loadTime) << std::endl;
	
	//Load the object into the objs vector

	this->objs.push_back(cube);
	this->objs.push_back(cb);

	for (int i = 0; i < this->objs.size(); i++) {
		this->nrOfTriangles += this->objs.at(i).getTriangles().size();
	}
}