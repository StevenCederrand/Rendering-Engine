#include "Application.h"

#define STB_IMAGE_IMPLEMENTATION


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

}

Application::~Application() {
	//Critical error when deleting this->window??
	delete this->window;
	delete this->shader;
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
	this->shader->setMat4("viewMatrix", this->camera->getViewMatrix());
	//Set Projection Matrix
	this->shader->setMat4("prjMatrix", this->prjMatrix);

	this->currentKey = ValidKeys::DUMMY;	
}

void Application::setupShaders() {
	//Our standard shader
	this->shader = new Shader(SHADERPATH + "vertShader.glsl", SHADERPATH + "geomShader.glsl" ,SHADERPATH + "fragShader.glsl");
}

void Application::loadObjects() {
	this->objectManager->readFromFile("ExampleOBJ.obj", "Cube", ObjectTypes::Standard, this->shader);
	this->objectManager->readFromFile("HeightMap3.png", "Terrain", ObjectTypes::HeightMapBased, this->shader);
	this->objectManager->readFromFile("ExampleOBJ.obj", "L1", ObjectTypes::LightSource, this->shader);
	this->objectManager->readFromFile("ExampleOBJ.obj", "L2", ObjectTypes::LightSource, this->shader);
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
	
	this->shader->use();

	this->shader->setInt("colorTexture", 0);
	this->shader->setInt("normalMap", 1);
	
	//shadows
	/*
	unsigned int depthWidth = 1024, depthHeight = 1024;
	unsigned int depthMap;
	unsigned int depthFramebuffer;
	depthMapFunction(depthWidth, depthHeight, depthMap, depthFramebuffer);

	shader->use();
	shader->setInt("shadowMap", 2);
	//end
	*/
	
	this->renderer.start();


	this->start();

	this->deltaTime->start();
	this->deltaTime->end();

	

	
	while (!glfwWindowShouldClose(this->window->getWindow())) {

		this->window->update();
		this->deltaTime->start();

		//Check input
		this->window->inputKey(this->currentKey);

		//Camera function 
		this->cameraHandler();
		this->shader->setVec3("cameraPos", this->camera->getCameraPosition());

		//Render the VAO with the loaded shader
		this->render();



		//shadows 
		//unsigned int depthWidth = 1024, depthHeight = 1024;
		/*
		glm::mat4 lightprjMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 50.0f);
		glm::mat4 lightViewMatrix = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
												glm::vec3(0.0f, 0.0f, 0.0f), 
												glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightMatrixes = lightprjMatrix * lightViewMatrix;


		this->window->setViewport1(depthWidth, depthHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, depthFramebuffer);
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textures.at(1));											//change to a new shader
		this->renderer.render(this->objectManager->getObjectloader(), this->objectManager->getObjects(), this->shader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		std::pair <int, int> temp;
		temp = window->getResolution();
		this->window->setViewport1(temp.first, temp.second);
		this->renderer.clearBuffers();
		shader->use();

		this->shader->setMat4("viewMatrix", this->camera->getViewMatrix());
		this->shader->setMat4("prjMatrix", this->prjMatrix);
		
		this->shader->setMat4("lightMatrixes", lightMatrixes);

		*/

		this->deltaTime->end();
		//Deltatime in ms
		
		this->deltaT = this->deltaTime->deltaTime();
		//std::cout << this->deltaT << std::endl;
		
	}
	this->objectManager->destroy();
	this->window->close();
}

void Application::render() {
	int temp1;
	this->renderer.clearBuffers();

	//Assign Textures
	for (int i = 0; i < this->textures.size(); i++) {
		//from 0 to 1
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures.at(i));
		temp1 = i;
	}
	//glActiveTexture(GL_TEXTURE0+(temp1+1));
	//glBindTexture(GL_TEXTURE_2D, depthMapT);
	this->shader->use();
	

	this->renderer.render(this->objectManager->getObjectloader(), this->objectManager->getObjects(), this->shader);

}

//Have this be in an object class
void Application::cameraHandler() {

	this->camera->update();

	if (this->currentKey != ValidKeys::DUMMY) {
		glm::vec3 cameraPos = camera->getCameraPosition();
		float yValue = objectManager->getElevation(cameraPos);
		//std::cout << this->deltaTime->deltaTime() << std::endl;
		camera->handleKeys(this->currentKey, yValue, this->deltaT);
	}
		
	this->currentKey = ValidKeys::DUMMY;

	this->shader->setMat4("worldMatrix", this->worldMatrix);
	// This is so that we can "walk" with wasd keys
	this->shader->setMat4("viewMatrix", this->camera->getViewMatrix());
}



void Application::depthMapFunction(unsigned int depthWidth, unsigned int depthHeight, unsigned int &depthMap, unsigned int &depthFramebuffer)
{
	//unsigned int depthWidth = 1024, depthHeight = 1024;

	//unsigned int depthMap;
	//unsigned int depthFramebuffer;
	glGenFramebuffers(1, &depthFramebuffer);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, depthWidth, depthHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBindFramebuffer(GL_FRAMEBUFFER, depthFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


}


