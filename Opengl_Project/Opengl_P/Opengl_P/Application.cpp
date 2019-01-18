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
}

void Application::start() {

	this->viewMatrix = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	
	this->prjMatrix = glm::perspective(glm::radians(65.0f), (float)this->window->getResolution().first / (float)this->window->getResolution().second, 0.1f, 20.0f);
	
	//Set world matrix
	GLint uniformLoc = glGetUniformLocation(this->gShaderProg, "worldMatrix");
	if (uniformLoc != -1) {
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &this->worldMatrix[0][0]);
	}
	//Set view matrix
	uniformLoc = glGetUniformLocation(this->gShaderProg, "viewMatrix");
	if (uniformLoc != -1) {
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &this->viewMatrix[0][0]);
	}
	//Set projection matrix
	uniformLoc = glGetUniformLocation(this->gShaderProg, "prjMatrix");
	if (uniformLoc != -1) {
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &this->prjMatrix[0][0]);
	}
	this->currentKey = ValidKeys::DUMMY;

	
}

void Application::setupShaders() {
	char buffer[1024];
	memset(buffer, 0, 1024);
	GLint compileResult = 0;

	//			VERTEX SHADER 
	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	std::ifstream shaderFile("vShader.glsl");
	std::string shaderCode((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	const char* shaderTextPtr = shaderCode.c_str();
	glShaderSource(vShader, 1, &shaderTextPtr, nullptr);

	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		glGetShaderInfoLog(vShader, 1024, nullptr, buffer);
		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}

	//			FRAGMENT SHADER

	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderFile.open("fShader.glsl");
	shaderCode.assign((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	shaderTextPtr = shaderCode.c_str();
	glShaderSource(fShader, 1, &shaderTextPtr, nullptr);

	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		memset(buffer, 0, 1024);

		glGetShaderInfoLog(vShader, 1024, nullptr, buffer);
		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}
	//				PROGRAM
	gShaderProg = glCreateProgram();
	glAttachShader(gShaderProg, vShader);
	glAttachShader(gShaderProg, fShader);
	glLinkProgram(gShaderProg);

	glGetProgramiv(gShaderProg, GL_LINK_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		memset(buffer, 0, 1024);
		glGetProgramInfoLog(gShaderProg, 1024, nullptr, buffer);

		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}

	glDetachShader(gShaderProg, vShader);
	glDetachShader(gShaderProg, fShader);
	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void Application::setupTriangle() {

	/*TriangleData triangle[3] = {
		//		VERTEX				COLOR			 UV
	{ 0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	0, 0 },
	{ -0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	0, 0 },
	{ 0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0, 0 },
	};
	*/
	std::chrono::high_resolution_clock timer;

	auto start = timer.now();
	Object object(OBJECTSPATH + "temp.obj");
	auto end = timer.now();

	std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - start;
	auto deltaTime = std::chrono::duration_cast<ms>(end - start).count(); // in ms
	std::cout << deltaTime << std::endl;
	std::cout << deltaTime << std::endl;
	
	glGenVertexArrays(1, &this->vertexAttrib);
	
	glBindVertexArray(this->vertexAttrib);
	//Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnableVertexAttribArray(0);
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	//Load the vertices 
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//Assign where in memory the positions are located	
	GLint vertexPos = glGetAttribLocation(this->gShaderProg, "position");
	if (vertexPos == -1) {
		std::cout << "Couldn't find vertexPos" << std::endl;
		return;
	}
	//Set the vertices in the glsl-code
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Set colours
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &this->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
	glm::vec3 red = glm::vec3(0, 255, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(red), red, GL_STATIC_DRAW);
	//Assign where in memory the colorData is located -- 
	GLint vertexCol = glGetAttribLocation(this->gShaderProg, "colorData");
	if (vertexCol == -1) {
		std::cout << "Couldn't find colorData" << std::endl;
		return;
	}
	//Set the colours in the glsl-code
	glVertexAttribPointer(vertexCol, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);	
}

//Runs every tick while the window is open
void Application::update() {
	this->setupShaders();
	this->setupTriangle();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glUseProgram(gShaderProg);
	this->start();

	std::chrono::high_resolution_clock timer;

	auto frameTime = timer.now();
	auto stop = timer.now();

	double deltaTime = 0.0f;

	while (!glfwWindowShouldClose(this->window->getWindow())) {
		frameTime = timer.now();

		//Check input
		this->window->inputKey(this->currentKey);

		this->rotate(deltaTime);
		
		//Render the VAO with the loaded shader
		this->render();
		this->window->update();
	
		stop = timer.now();

		std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - frameTime;
		deltaTime = std::chrono::duration_cast<ms>(stop - frameTime).count() / 1000; 
	}
	glfwTerminate();
}

void Application::render() {
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (this->gShaderProg != 0) {
		glUseProgram(this->gShaderProg);
	}

	if (this->vertexAttrib != 0) {
		glBindVertexArray(this->vertexAttrib);
	}

	//12*3 is used here because we are inputing 12 triangles -- change this later
	glDrawArrays(GL_TRIANGLES, 0, 12*3);

}

//Have this be in an object class
void Application::rotate(float deltaTime) {

	if (this->currentKey == ValidKeys::W) {
		this->xRotation += rotationVal / deltaTime;
		rotations.getXRotationAtAngle(this->xRotation, this->worldMatrix);
	}
	else if (this->currentKey == ValidKeys::S) {
		this->xRotation -= rotationVal / deltaTime;
		rotations.getXRotationAtAngle(this->xRotation, this->worldMatrix);
	}
	else if (this->currentKey == ValidKeys::A) {
		this->yRotation -= rotationVal / deltaTime;
		rotations.getYRotationAtAngle(this->yRotation, this->worldMatrix);
	}
	else if (this->currentKey == ValidKeys::D) {
		this->yRotation += rotationVal / deltaTime;
		rotations.getYRotationAtAngle(this->yRotation, this->worldMatrix);
	}
	else if (this->currentKey == ValidKeys::Q) {
		this->zRotation -= rotationVal / deltaTime;
		rotations.getZRotationAtAngle(this->zRotation, this->worldMatrix);
	}
	else if (this->currentKey == ValidKeys::E) {
		this->zRotation += rotationVal / deltaTime;
		rotations.getZRotationAtAngle(this->zRotation, this->worldMatrix);
	}
	this->currentKey = ValidKeys::DUMMY;
	//This does need to be called everyframe. Otherwise the new rotation won't be sent to the GPU
	GLint worldMatrixLoc = glGetUniformLocation(gShaderProg, "worldMatrix");
	if (worldMatrixLoc != -1) {
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &this->worldMatrix[0][0]);
	}
}

/*
void Application::setupOBJ() {
	//bool res = this->loadOBJ("", this->vertices, this->uv, this->normals);
	
	std::string paths = OBJECTSPATH + "temp.obj";
	std::string path = "Rendering - Engine\\Objects\\temp.obj";
	Object obj = Object();
	obj.loadModel(paths);

	
	Fileloader loader;
	loader.loadFile("Rendering - Engine\\Objects\\temp.obj");
}

bool Application::loadOBJ(std::string path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outUV, std::vector<glm::vec3>& outNormals) {
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVertices, tempNormals;
	std::vector<glm::vec2> tempUVs;

	//Open the file
	FILE* file = fopen(path.c_str(), "r");
	if (file == NULL) {
		std::cout << "No File" << std::endl;
		return false;
	}

	while (1) {
		char lineHeader[128];

		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) {
			break;
		}
		else {
			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				tempVertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				tempUVs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				tempNormals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string v1, v2, v3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					std::cout << "Can't work with this file. SIMPLIFY" << std::endl;
					return false;
				}
				for (int i = 0; i < 3; i++) {
					vertexIndices.push_back(vertexIndex[i]);
					normalIndices.push_back(normalIndex[i]);
					uvIndices.push_back(uvIndex[i]);
				}
			}
		}
		
	}
	for (uint8_t i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertIn = vertexIndices[i];
		glm::vec3 vertex = tempVertices[vertIn - 1];
		outVertices.push_back(vertex);
	}
	for (uint8_t i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIn = normalIndices[i];
		glm::vec3 normal = tempNormals[normalIn - 1];
		outNormals.push_back(normal);
	}
	for (uint8_t i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIn = uvIndices[i];
		glm::vec2 uv = tempUVs[uvIn - 1];
		outUV.push_back(uv);
	}
		
	return true;
}
*/