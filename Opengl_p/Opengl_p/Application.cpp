#include "Application.h"

#define STB_IMAGE_IMPLEMENTATION


//Creates a default window. 
Application::Application() {

	this->window = new WND();
	this->window->start();
	this->renderer = Renderer(this->window->getResolution().first, this->window->getResolution().second);
}

//Creates a window with a specific size
Application::Application(int WNDW, int WNDH) {
	this->window = new WND(WNDW, WNDH);
	this->window->start();
	this->objectManager = new ObjectManager();
	this->deltaTime = new Deltatime();
	this->renderer = Renderer(this->window->getResolution().first, this->window->getResolution().second);

}

Application::~Application() {
	delete this->window;
	delete this->shaderGeometryPass;
	delete this->camera;
	delete this->objectManager;
	delete this->deltaTime;

}
//Setup the matrixes
void Application::start() {

	//this->viewMatrix = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	this->camera = new Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), this->window->getWindow());

	this->prjMatrix = glm::perspective(glm::radians(65.0f), (float)this->window->getResolution().first / (float)this->window->getResolution().second, 0.1f, 50.0f);
	
	//Set View Matrix
	this->shaderManager.getSpecific("geometryPass")->setMat4("viewMatrix", this->camera->getViewMatrix());
	//Set Projection Matrix
	this->shaderManager.getSpecific("geometryPass")->setMat4("prjMatrix", this->prjMatrix);

	this->currentKey = ValidKeys::DUMMY;
}

void Application::setupShaders() {

	this->shaderManager.insertShader(SHADERPATH + "vertShader.glsl", SHADERPATH + "geomShader.glsl",
		SHADERPATH + "fragShader.glsl", "geometryPass");
	this->shaderManager.insertShader(SHADERPATH + "deferred_shading_vs.glsl",
		SHADERPATH + "deferred_shading_fs.glsl", "lightPass");

	//Our standard shader
	this->shaderGeometryPass = new Shader(SHADERPATH + "vertShader.glsl", SHADERPATH + "geomShader.glsl", SHADERPATH + "fragShader.glsl");
	this->shaderLightPass = new Shader(SHADERPATH + "deferred_shading_vs.glsl", SHADERPATH + "deferred_shading_fs.glsl");
}

void Application::loadObjects() {

	this->objectManager->readFromFile("ExampleOBJ.obj", "Cube", ObjectTypes::Standard, 
		this->shaderManager.getSpecific("geometryPass"));

	this->objectManager->readFromFile("HeightMap3.png", "Terrain", ObjectTypes::HeightMapBased, 
		this->shaderManager.getSpecific("geometryPass"));

	this->objectManager->readFromFile("ExampleOBJ.obj", "L1", ObjectTypes::LightSource, 
		this->shaderManager.getSpecific("geometryPass"));	//Should be "lightpass"
	
	this->objectManager->readFromFile("ExampleOBJ.obj", "L2", ObjectTypes::LightSource, 
		this->shaderManager.getSpecific("geometryPass"));	//Should be "lightpass"
}

void Application::setupTextures(unsigned int &texture, std::string name) {
	//Key-ShadowMap
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
	this->loadObjects();


	for (int i = 0; i < 2; i++) {
		unsigned int tex;
		if (i == 0) {
			this->setupTextures(tex, this->objectManager->getObjects().at(1).getTexture(Texturetypes::Diffuse).name);//this->objs.at(0).getTexture(Texturetypes::Diffuse).name);
		}
		else {
			this->setupTextures(tex, this->objectManager->getObjects().at(1).getTexture(Texturetypes::Normal).name);
		}
		this->textures.push_back(tex);
	}

	this->shaderManager.getSpecific("geometryPass")->use();

	this->shaderManager.getSpecific("geometryPass")->setInt("colorTexture", 0);
	this->shaderManager.getSpecific("geometryPass")->setInt("normalMap", 1);

	this->shaderLightPass->use();
	this->shaderLightPass->setInt("lightCount", this->objectManager->getLightCount());

	//Configure Defered shading
	this->renderer.start();
	this->renderer.setupLightPassShader(this->shaderLightPass);
	this->renderer.setLightCount(this->objectManager->getLightCount());
	//Configure Matrices
	this->start();

	//Configure Deltatimer
	this->deltaTime->start();
	this->deltaTime->end();

	while (!glfwWindowShouldClose(this->window->getWindow())) {

		this->window->update();
		this->deltaTime->start();

		//Check input
		this->window->inputKey(this->currentKey);

		//Camera function 
		this->cameraHandler();

		//Render the VAO with the loaded shader
		this->render();

		this->deltaTime->end();

		//Deltatime in ms
		this->deltaT = this->deltaTime->deltaTime();
	}
	this->objectManager->destroy();
	this->window->close();
}

void Application::render() {
	this->renderer.clearBuffers();

	//Assign Textures
	for (int i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures.at(i));
	}

	this->shaderManager.getSpecific("geometryPass")->use();


	this->renderer.render(this->objectManager->getObjectloader(), this->objectManager->getObjects(), this->shaderManager.getSpecific("geometryPass"));
}

//Have this be in an object class
void Application::cameraHandler() {

	this->camera->update();

	if (this->currentKey != ValidKeys::DUMMY) {
		glm::vec3 cameraPos = camera->getCameraPosition();
		float yValue = objectManager->getElevation(cameraPos);
		camera->handleKeys(this->currentKey, yValue, this->deltaT);
	}

	this->currentKey = ValidKeys::DUMMY;

	this->shaderManager.getSpecific("geometryPass")->setMat4("worldMatrix", this->worldMatrix);
	// This is so that we can "walk" with wasd keys
	this->shaderManager.getSpecific("geometryPass")->setMat4("viewMatrix", this->camera->getViewMatrix());
	//Configure Camera Positioning
	this->shaderManager.getSpecific("geometryPass")->use();
	this->shaderManager.getSpecific("geometryPass")->setVec3("cameraPos", this->camera->getCameraPosition());
	this->shaderManager.getSpecific("lightPass")->use();
	this->shaderManager.getSpecific("lightPass")->setVec3("cameraPos", this->camera->getCameraPosition());
}

