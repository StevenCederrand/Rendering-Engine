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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	this->loadObjects();

	//Load the vertices into memory
	glGenVertexArrays(1, &this->vertexAttrib);
	glBindVertexArray(this->vertexAttrib);
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

	
	std::vector<Vertex> meshData;

	meshData = objs.at(0).getMesh().verts;
	
	int totalSize = meshData.size() * sizeof(Vertex);

	//Load vertices into the buffer
	glBufferData(GL_ARRAY_BUFFER, totalSize, &meshData[0], GL_STATIC_DRAW);
	
	//Assign where in memory the positions are located	
	GLint attribLocation = glGetAttribLocation(this->shader->getShaderID(), "position");
	if (attribLocation == -1) {
		std::cout << "ERROR::LOCATING::VERTEX::POS" << std::endl;
		return;
	}
	
	//Set the vertices in the glsl-code
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(attribLocation);
	this->setColours();
	//Load normals
	attribLocation = 1; glGetAttribLocation(this->shader->getShaderID(), "normal");
	if (attribLocation == -1) {
		std::cout << "ERROR::LOCATING::NORMAL::POS" << std::endl;
		return;
	}
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(glm::vec3)));
	glEnableVertexAttribArray(attribLocation);

	//Load uv's
	attribLocation = 2;//glGetAttribLocation(this->shader->getShaderID(), "uv");
	if (attribLocation == -1) {
		std::cout << "ERROR::LOCATING::UV::POS" << std::endl;
		return;
	}
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(float) * 6));
	glEnableVertexAttribArray(attribLocation);

}


void Application::setupGround()
{
	struct TriangleVertex{float x, y, z;};
	std::vector<float> elevation;
	int width = 0;
	int height = 0;
	fileloader.loadMap(OBJECTSPATH + "HeightMap2.PNG", width, height, elevation);

	int size = width*height;
	int counter = 0;
	int index = 0;
	//create a trianglevertex struct of the size, width*height
	TriangleVertex *triangleVertices = new TriangleVertex[size];
	 //delete this senare
	/*
	for (size_t j = 0; j < height; j++)
	{
		for (size_t i = 0; i < width; i++)
		{
			index = height * j + i;
			triangleVertices[index].x = (float)i;
			triangleVertices[index].y = elevation[counter] /10;//divide by a number so that it looks more "flat"
			triangleVertices[index].z = (float)j;
			counter++;
		}
	}
	*/
	Object objMap = Object();
	Mesh meshMap;
	int position1, position2, position3, position4;
	glm::vec3 normal1, normal2;
	std::vector<Vertex> mapPosition;
	Vertex vert;
	for (size_t j = 0; j < (height-1); j++)
	{
		for (size_t i = 0; i < (width-1); i++)
		{
			position1 = (height * j) + i;				//upper left			
			triangleVertices[position1].x = (float)i;
			triangleVertices[position1].y = elevation[position1] * 0.1f;//divide by a number so that it looks more "flat"
			triangleVertices[position1].z = (float)j;

			position2 = (height * j) + (i + 1);			//upper right
			triangleVertices[position2].x = (float)i;
			triangleVertices[position2].y = elevation[position2] * 0.1f;;//divide by a number so that it looks more "flat"
			triangleVertices[position2].z = (float)j;

			position3 = (height *(j + 1)) + i;			//bottom left
			triangleVertices[position3].x = (float)i;
			triangleVertices[position3].y = elevation[position3] * 0.1f;;//divide by a number so that it looks more "flat"
			triangleVertices[position3].z = (float)j;

			position4 = (height *(j + 1)) + (i + 1);	//bottom right
			triangleVertices[position4].x = (float)i;
			triangleVertices[position4].y = elevation[position4] * 0.1f;;//divide by a number so that it looks more "flat"
			triangleVertices[position4].z = (float)j;

			glm::vec3 firstV = glm::vec3(triangleVertices[position1].x, triangleVertices[position1].y, triangleVertices[position1].z);
			glm::vec3 secondV = glm::vec3(triangleVertices[position2].x, triangleVertices[position2].y, triangleVertices[position2].z);

			glm::vec3 thirdV = glm::vec3(triangleVertices[position3].x, triangleVertices[position3].y, triangleVertices[position3].z);
			glm::vec3 fourthV = glm::vec3(triangleVertices[position4].x, triangleVertices[position4].y, triangleVertices[position4].z);

			normal1 = glm::normalize(glm::cross(firstV-secondV, firstV-thirdV));
			normal2 = glm::normalize(glm::cross(fourthV-thirdV, fourthV-secondV));
			//first vertex to first triangle
			vert.position=(firstV);
			vert.normal = (normal1);
			mapPosition.push_back(vert);

			//second vertex to first triangle
			vert.position = (secondV);
			vert.normal = (normal1);
			mapPosition.push_back(vert);

			//third vertex to first triangle
			vert.position = (thirdV);
			vert.normal = (normal1);
			mapPosition.push_back(vert);

			//first vertex to second triangle
			vert.position = (secondV);
			vert.normal = (normal2);
			mapPosition.push_back(vert);

			//second vertex to second triangle
			vert.position = (thirdV);
			vert.normal = (normal2);
			mapPosition.push_back(vert);

			//third vertex to second triangle
			vert.position = (fourthV);
			vert.normal = (normal2);
			mapPosition.push_back(vert);
		
			

		}
	}
			//change this!
			meshMap.verts = mapPosition;
			//setMesh(A Mesh) 
			objMap.setMesh(meshMap);
				//pusha map
			this->objs.push_back(objMap);
			
	delete triangleVertices;
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
		std::cout << "FOUND TEXTURE" << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		std::cout << "Generated mipmap" << std::endl;
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR::LOADING::TEXTURE" << std::endl;
	}
	stbi_image_free(data);
}

//Runs every tick while the window is open
void Application::update() {

	this->setupShaders();
	this->setupObjects();

	for (int i = 0; i < this->objs.at(0).getMaterial().textures.size(); i++ ) {
		std::cout << this->objs.at(0).getMaterial().textures.at(i).type << std::endl;
	}
	
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

	glDrawArrays(GL_TRIANGLES, 0, this->objs.at(0).getMesh().verts.size());
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
	Object cube = this->fileloader.readFile(OBJECTSPATH + "ExampleOBJ.obj");

	auto end = timer.now();

	//Calculate the time it took to load
	std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - start;
	auto loadTime = std::chrono::duration_cast<ms>(end - start).count(); // in ms
	std::cout << "Loadtime(ms): " + std::to_string(loadTime) << std::endl;
	
	//Load the object into the objs vector
	this->objs.push_back(cube);
}

void Application::setColours() {
	this->shader->use();
	this->shader->setVec3("ambientCol", this->objs.at(0).getMaterial().ambientCol);
	this->shader->setVec3("diffuseCol", this->objs.at(0).getMaterial().diffuseCol);
	this->shader->setVec3("specCol", this->objs.at(0).getMaterial().specularCol);
	this->shader->setFloat("transparency", this->objs.at(0).getMaterial().transparency);
	this->shader->setFloat("specularWeight", this->objs.at(0).getMaterial().specularWeight);
}