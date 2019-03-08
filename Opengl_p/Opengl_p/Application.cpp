#include "Application.h"

//Creates a default window. 
Application::Application() {

	this->window = new WND();
	this->window->start();
}

//Creates a window with a specific size
Application::Application(int WNDW, int WNDH) {

	this->window = new WND(WNDW, WNDH);
	this->window->start();
	this->objectManager = new ObjectManager();
	this->deltaTime = new Deltatime();
	this->shaderManager = new ShaderManager();

}

Application::~Application() {
	//Critical error when deleting this->window??
	delete this->window;
	delete this->camera;
	delete this->objectManager;
	delete this->deltaTime;
	delete this->shaderManager;
}

//Setup the matrixes
void Application::start() {

	this->camera = new Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), this->window->getWindow());

	this->prjMatrix = glm::perspective(glm::radians(65.0f), (float)this->window->getResolution().first / (float)this->window->getResolution().second, 0.1f, 50.0f);
	
	//Set View Matrix
	this->shaderManager->getSpecific("GeometryPass")->setMat4("viewMatrix", this->camera->getViewMatrix());
	//Set Projection Matrix
	this->shaderManager->getSpecific("GeometryPass")->setMat4("prjMatrix", this->prjMatrix);

	this->currentKey = ValidKeys::DUMMY;
}

void Application::setupShaders() {
	this->shaderManager->insertShader(
		SHADERPATH + "GeometryPassVS.glsl",
		SHADERPATH + "GeometryPassGS.glsl",
		SHADERPATH + "GeometryPassFS.glsl", "GeometryPass");

	Shader* lightPass = this->shaderManager->insertShader(
		SHADERPATH + "LightPassVS.glsl",
		SHADERPATH + "LightPassFS.glsl", "LightPass");

	lightPass->use();
	lightPass->setInt("positionBuffer", 0);
	lightPass->setInt("normalBuffer", 1);
	lightPass->setInt("colourBuffer", 2);
}

void Application::loadObjects() {
	this->objectManager->readFromFile("ExampleOBJ.obj", "Cube", ObjectTypes::Standard, this->shaderManager->getSpecific("GeometryPass"));
	this->objectManager->readFromFile("HeightMap3.png", "Terrain", ObjectTypes::HeightMapBased, this->shaderManager->getSpecific("GeometryPass"));
	this->objectManager->readFromFile("ExampleOBJ.obj", "L1", ObjectTypes::LightSource, this->shaderManager->getSpecific("LightPass"));
	this->objectManager->readFromFile("ExampleOBJ.obj", "L2", ObjectTypes::LightSource, this->shaderManager->getSpecific("LightPass"));
}

void Application::setupTextures(unsigned int &texture, std::string name) {
	//Key-ShadowMap
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//std::string path = OBJECTSPATH + name;

	//int width, height, nrChannels;

	//unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	//if (data) {
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//	std::cout << "GENERATED::TEXTURE" << std::endl;
	//}
	//else {
	//	std::cout << "ERROR::LOADING::TEXTURE" << std::endl;
	//}
	//stbi_image_free(data);
}

//Runs every tick while the window is open
void Application::update() {
	this->setupShaders();
	this->loadObjects();
	
	/*
	for (int i = 0; i < 2; i++) {
		unsigned int tex;
		if (i == 0) {
			this->setupTextures(tex, this->objectManager->getObjects().at(0).getTexture(Texturetypes::Diffuse).name);
		}
		else {
			this->setupTextures(tex, this->objectManager->getObjects().at(0).getTexture(Texturetypes::Normal).name);
		}
		this->textures.push_back(tex);
	}
	geometryPass->use();
	geometryPass->setInt("colorTexture", 0);
	geometryPass->setInt("normalMap", 1);
	*/
	Shader* geometryPass = this->shaderManager->getSpecific("GeometryPass");
	this->renderer.start(this->window->getResolution().first, this->window->getResolution().second);


	this->start();

	this->deltaTime->start();
	this->deltaTime->end();

	Shader* lightPass = this->shaderManager->getSpecific("LightPass");
	lightPass->use();
	lightPass->setInt("lightCount", this->objectManager->getLightCount());

	while (!glfwWindowShouldClose(this->window->getWindow())) {
		this->window->update();

		this->deltaTime->start();

		//Check input
		this->window->inputKey(this->currentKey);

		//Camera function 
		this->cameraHandler(geometryPass);
		lightPass->use();
		lightPass->setVec3("cameraPos", camera->getCameraPosition());

		//Render the VAO with the loaded shader
		this->render();

		//Deltatime in ms
		this->deltaTime->end();

		this->deltaT = this->deltaTime->deltaTime();
	}
	//Quit the program
	this->end();
}

void Application::render() {
	this->renderer.clearBuffers();
	this->acceleration->frontBackRendering(objectManager->handleObjects(), camera->getCameraPosition());

	//Assign Textures
	//for (int i = 0; i < this->textures.size(); i++) {
	//	glActiveTexture(GL_TEXTURE0 + i);
	//	glBindTexture(GL_TEXTURE_2D, textures.at(i));
	//}

	this->renderer.deferredRender(objectManager->getObjects(), this->shaderManager);
}

//Have this be in an object class
void Application::cameraHandler(Shader* geometryPass) {

	this->camera->update();

	if (this->currentKey != ValidKeys::DUMMY) {
		glm::vec3 cameraPos = camera->getCameraPosition();
		float yValue = objectManager->getElevation(cameraPos);
		camera->handleKeys(this->currentKey, yValue, (float)this->deltaT);
	}

	this->currentKey = ValidKeys::DUMMY;
	geometryPass->use();
	geometryPass->setMat4("worldMatrix", this->worldMatrix);
	// This is so that we can "walk" with wasd keys
	geometryPass->setMat4("viewMatrix", this->camera->getViewMatrix());
}

void Application::end() {
	for (size_t i = 0; i < this->objectManager->getObjects().size(); i++) {
		if (this->objectManager->getObjects().at(i).type == ObjectTypes::LightSource) {
			this->objectManager->destroyLight(i);
		}
	}
	this->objectManager->destroy();
	this->renderer.clear();
	this->window->close();
}