#include "Application.h"



#define STB_IMAGE_IMPLEMENTATION
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
	this->objectManager = new ObjectManager();

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
	this->shader = new Shader(SHADERPATH + "tempVShader.glsl", SHADERPATH + "tempGShader.glsl" ,SHADERPATH + "tempFShader.glsl");
	//this->shader = new Shader(SHADERPATH + "vShader.glsl", SHADERPATH + "fShader.glsl");
}

void Application::setupObjects() {
	//Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	this->loadObjects();

	//Load the vertices into memory
	glGenVertexArrays(1, &this->vertexAttrib);
	glBindVertexArray(this->vertexAttrib);
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	
	std::vector<Vertex> meshData;
	this->objs = this->objectManager->getObjects();
	meshData = objs.at(0).getMesh().verts;

	int totalSize = meshData.size() * sizeof(Vertex);

	//Load vertices into the buffer
	glBufferData(GL_ARRAY_BUFFER, totalSize, &meshData[0], GL_STATIC_DRAW);

	this->objectManager->setupObjects(this->shader);
}


void Application::setupGround()
{
	this->objectManager->loadMap("HeightMap3.PNG");

	glGenVertexArrays(1, &this->vertexAttrib);
	glBindVertexArray(this->vertexAttrib);
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

	std::vector<Vertex> meshData;
	this->objs = this->objectManager->getObjects();
	meshData = objs.at(0).getMesh().verts;

	int totalSize = meshData.size() * sizeof(Vertex);

	//Load vertices into the buffer
	glBufferData(GL_ARRAY_BUFFER, totalSize, &meshData[0], GL_STATIC_DRAW);

	this->objectManager->setupObjects(this->shader);
	
}

void Application::setupTextures(unsigned int &texture, std::string name) {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	std::string path = OBJECTSPATH + name;

	int width, height, nrChannels;
	
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "GENERATED::TEXTURE" << std::endl;
	}
	else {
		std::cout << "ERROR::LOADING::TEXTURE" << std::endl;
	}
	stbi_image_free(data);
}

//Runs every tick while the window is open
void Application::update() {

	this->setupShaders();
	//this->setupGround();
	this->setupObjects();


	for (int i = 0; i < 2; i++) {
		unsigned int tex;
		if (i == 0) {
			this->setupTextures(tex, this->objs.at(0).getTexture(Texturetypes::Diffuse).name);
		}
		else {
			this->setupTextures(tex, this->objs.at(0).getTexture(Texturetypes::Normal).name);
		}
		this->textures.push_back(tex);
	}
	
	this->shader->use();

	this->shader->setInt("colorTexture", 0);
	this->shader->setInt("normalMap", 1);

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
		this->shader->setVec3("cameraPos", this->camera->getCameraPosition());

		//Render the VAO with the loaded shader
		this->render();

		stop = timer.now();
		//Deltatime in ms
		std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - frameTime;
		deltaTime = std::chrono::duration_cast<ms>(stop - frameTime).count() / 1000; 
		this->window->update();
	}
	glDeleteVertexArrays(1, &vertexAttrib);
	glDeleteBuffers(1, &vertexBuffer);
	this->window->close();
}

void Application::render() {
	glClearColor(0.1f, 0.1f, 0.1f, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (int i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures.at(i));
	}
	
	this->shader->use();
	glBindVertexArray(this->vertexAttrib);

	glDrawArrays(GL_TRIANGLES, 0, this->objectManager->getObjects().at(0).getMesh().verts.size());
}

//Have this be in an object class
void Application::cameraHandler() {

	this->camera->update();

	if (this->currentKey != ValidKeys::DUMMY) {
		glm::vec3 cameraPos = camera->getCameraPosition();
		float yValue = objectManager->getElevation(cameraPos);
		camera->handleKeys(this->currentKey, yValue);
	}
		
	this->currentKey = ValidKeys::DUMMY;

	this->shader->setMat4("worldMatrix", this->worldMatrix);
	// This is so that we can "walk" with wasd keys
	this->shader->setMat4("viewMatrix", this->camera->getViewMatrix());
}

void Application::loadObjects() {
	this->objectManager->loadObject("ExampleOBJ.obj");


	//Observe the time it takes to load all of the objects
	std::chrono::high_resolution_clock timer;
	auto start = timer.now();

	//Insert all of the objects here!
	Object cube = this->fileloader.readFile(OBJECTSPATH + "ExampleOBJ.obj");

	auto end = timer.now();

	//Calculate the time it took to load
	std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - start;
	auto loadTime = std::chrono::duration_cast<ms>(end - start).count(); // in ms
	std::cout << "Loadtime(ms): " + std::to_string(loadTime) << std::endl;
	
	//Load the object into the objs vector
	//this->objs.push_back(cube);
}

void Application::setColours() {
	this->shader->use();
	this->objs.at(0).assignMaterial(this->shader);
}