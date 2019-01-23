#include "Application.h"

using ms = std::chrono::duration<float, std::milli>;

// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};


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
	delete this->window;
	delete this->camera;
	delete this->shader;
}
//Setup the matrixes
void Application::start() {

	//this->viewMatrix = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	this->camera = new Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), this->window->getWindow());

	this->prjMatrix = glm::perspective(glm::radians(65.0f), (float)this->window->getResolution().first / (float)this->window->getResolution().second, 0.1f, 20.0f);
	
	//Set world matrix
	GLint uniformLoc = glGetUniformLocation(this->shader->getShaderID(), "worldMatrix");
	if (uniformLoc != -1) {
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &this->worldMatrix[0][0]);
	}
	//Set view matrix
	uniformLoc = glGetUniformLocation(this->shader->getShaderID(), "viewMatrix");
	if (uniformLoc != -1) {
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &this->camera->getViewMatrix()[0][0]);
	}
	//Set projection matrix
	uniformLoc = glGetUniformLocation(this->shader->getShaderID(), "prjMatrix");
	if (uniformLoc != -1) {
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &this->prjMatrix[0][0]);
	}
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
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

	std::vector<glm::vec3> vertices;

	//Load all vertices
	for (int i = 0; i < this->objs.size(); i++) {
		for (int j = 0; j < this->objs.at(i).getOrderedVertices().size(); j++) {
			vertices.push_back(this->objs.at(i).getOrderedVertices().at(j).vertex);
		}
	}

	int totalSize = 0;
	for (int i = 0; i < this->objs.size(); i++) {
		totalSize += this->objs.at(i).getByteSize();
	}
	
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

	//---- Set colours ----
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &this->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
	glm::vec3 col = glm::vec3(0, 244, 0);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &col[0], GL_STATIC_DRAW);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &col[0], GL_STATIC_DRAW);
	//Assign where in memory the colorData is located -- 
	GLint vertexCol = glGetAttribLocation(this->shader->getShaderID(), "colorData");
	if (vertexCol == -1) {
		std::cout << "Couldn't find colorData" << std::endl;
		return;
	}
	//Set the colours in the glsl-code
	glVertexAttribPointer(vertexCol, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 0));
}

//Runs every tick while the window is open
void Application::update() {
	this->setupShaders();
	this->setupObjects();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	this->shader->use();
	//glUseProgram(gShaderProg);
	this->start();

	std::chrono::high_resolution_clock timer;

	auto frameTime = timer.now();
	auto stop = timer.now();

	double deltaTime = 0.0f;

	while (!glfwWindowShouldClose(this->window->getWindow())) {
		frameTime = timer.now();

		//Check input
		this->window->inputKey(this->currentKey);

		//If no key is pressed
		
		this->cameraHandler();
		
		

		//Render the VAO with the loaded shader
		this->render();
		this->window->update();
		stop = timer.now();

		//Deltatime in ms
		std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - frameTime;
		deltaTime = std::chrono::duration_cast<ms>(stop - frameTime).count() / 1000; 
		
	}
	glfwTerminate();
}

void Application::render() {
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (this->shader->getShaderID() != 0) {
		this->shader->use();
		//glUseProgram(this->gShaderProg);
	}

	if (this->vertexAttrib != 0) {
		glBindVertexArray(this->vertexAttrib);
	}
	
	//12*3 is used here because we are inputing 12 triangles -- change this later
	glDrawArrays(GL_TRIANGLES, 0, this->objs.size() * this->nrOfTriangles * 3);

}

//Have this be in an object class
void Application::cameraHandler() {

	this->camera->update();
	if (this->currentKey != ValidKeys::DUMMY) {
		camera->handleKeys(this->currentKey);
	}

	this->currentKey = ValidKeys::DUMMY;

	//For model-based rotations
	GLint worldMatrixLoc = glGetUniformLocation(this->shader->getShaderID(), "worldMatrix");
	if (worldMatrixLoc != -1) {
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &this->worldMatrix[0][0]);
	}
	
	// This is so that we can "walk" with wasd keys
	//this->viewMatrix = this->camera->getViewMatrix(); //glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	GLint viewMatrixLoc = glGetUniformLocation(this->shader->getShaderID(), "viewMatrix");
	if (viewMatrixLoc != -1) {
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &this->camera->getViewMatrix()[0][0]);
	}
}

void Application::loadObjects() {

	//Observe the time it takes to load all of the objects
	std::chrono::high_resolution_clock timer;
	auto start = timer.now();
	
	//Insert all of the objects here!
	//Object object(OBJECTSPATH + "Monkey.obj");
	Object monkey = this->fileloader.loadObj(OBJECTSPATH + "Monkey.obj");

	//Object obj(OBJECTSPATH + "test.obj");
	//Object objj(OBJECTSPATH + "temp3.obj");
	auto end = timer.now();

	//Calculate the time it took to load
	std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - start;
	auto loadTime = std::chrono::duration_cast<ms>(end - start).count(); // in ms
	std::cout << "Loadtime(ms): " + std::to_string(loadTime) << std::endl;
	
	//Load the object into the objs vector
	this->objs.push_back(monkey);
	//this->objs.push_back(obj);
	//this->objs.push_back(objj);

	for (int i = 0; i < this->objs.size(); i++) {
		this->nrOfTriangles += this->objs.at(i).getTriangles().size();
	}
}