#include "Shader.h"

Shader::Shader() {

}

Shader::Shader(std::string vPath, std::string fPath) {

	std::string vCode; //Vertex shader code
	std::string fCode; //Fragment shader code

	//Shader files
	std::ifstream vShader;
	std::ifstream fShader;
	//open
	vShader.open(vPath);
	fShader.open(fPath);
	//Streamed data
	std::stringstream vStream;
	std::stringstream fStream;

	vStream << vShader.rdbuf();
	fStream << fShader.rdbuf();

	vShader.close();
	fShader.close();
	//Read the vStream data
	vCode = vStream.str();
	fCode = fStream.str();

	//	  ___Compile___
	GLint compileResult;
	char buffer[1024];

	// ___Vertex Shader___ 
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* shaderTxtPtr = vCode.c_str();
	glShaderSource(vertexShader, 1, &shaderTxtPtr, nullptr);
	glCompileShader(vertexShader);
	//Debug
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		glGetShaderInfoLog(vertexShader, 1024, nullptr, buffer);
		std::cout << "COMPILATION::ERROR::VERTEX::SHADER" << std::endl;
		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}

	// ___Fragment Shader___ 
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderTxtPtr = fCode.c_str();
	glShaderSource(fragmentShader, 1, &shaderTxtPtr, nullptr);
	glCompileShader(fragmentShader);
	//Debug
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileResult);
	if (!compileResult) {
		glGetShaderInfoLog(fragmentShader, 1024, nullptr, buffer);
		std::cout << "COMPILATION::ERROR::FRAGMENT::SHADER" << std::endl;
		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}


	// ___PROGRAM___
	this->shaderProg = glCreateProgram();
	glAttachShader(this->shaderProg, vertexShader);
	glAttachShader(this->shaderProg, fragmentShader);
	glLinkProgram(this->shaderProg);
	//Debug
	glGetProgramiv(this->shaderProg, GL_LINK_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		memset(buffer, 0, 1024);
		glGetProgramInfoLog(this->shaderProg, 1024, nullptr, buffer);
		std::cout << "LINK::ERROR::SHADER::PROGRAM" << std::endl;
		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}

	glDetachShader(this->shaderProg, vertexShader);
	glDetachShader(this->shaderProg, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(std::string vPath, std::string gPath, std::string fPath) {

	std::string vCode; //Vertex shader code
	std::string gCode; //Geometry shader code
	std::string fCode; //Fragment shader code

	//Shader files
	std::ifstream vShader;
	std::ifstream gShader;
	std::ifstream fShader;

	//open
	vShader.open(vPath);
	gShader.open(gPath);
	fShader.open(fPath);
	//Streamed data
	std::stringstream vStream;
	std::stringstream gStream;
	std::stringstream fStream;

	vStream << vShader.rdbuf();
	gStream << gShader.rdbuf();
	fStream << fShader.rdbuf();

	vShader.close();
	gShader.close(),
	fShader.close();

	//Read the vStream data
	vCode = vStream.str();
	gCode = gStream.str();
	fCode = fStream.str();

	//	  ___Compile___
	GLint compileResult;
	char buffer[1024];

	// ___Vertex Shader___ 
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* shaderTxtPtr = vCode.c_str();
	glShaderSource(vertexShader, 1, &shaderTxtPtr, nullptr);
	glCompileShader(vertexShader);
	//Debug
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		glGetShaderInfoLog(vertexShader, 1024, nullptr, buffer);
		std::cout << "COMPILATION::ERROR::VERTEX::SHADER" << std::endl;
		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}

	// ___Geometry Shader___ 
	unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	shaderTxtPtr = gCode.c_str();
	glShaderSource(geometryShader, 1, &shaderTxtPtr, nullptr);
	glCompileShader(geometryShader);
	//Debug
	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		glGetShaderInfoLog(vertexShader, 1024, nullptr, buffer);
		std::cout << "COMPILATION::ERROR::VERTEX::SHADER" << std::endl;
		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}

	// ___Fragment Shader___ 
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderTxtPtr = fCode.c_str();
	glShaderSource(fragmentShader, 1, &shaderTxtPtr, nullptr);
	glCompileShader(fragmentShader);
	//Debug
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileResult);
	if (!compileResult) {
		glGetShaderInfoLog(fragmentShader, 1024, nullptr, buffer);
		std::cout << "COMPILATION::ERROR::FRAGMENT::SHADER" << std::endl;
		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}


	// ___PROGRAM___
	this->shaderProg = glCreateProgram();
	glAttachShader(this->shaderProg, vertexShader);
	glAttachShader(this->shaderProg, geometryShader),
	glAttachShader(this->shaderProg, fragmentShader);
	glLinkProgram(this->shaderProg);
	//Debug
	glGetProgramiv(this->shaderProg, GL_LINK_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		memset(buffer, 0, 1024);
		glGetProgramInfoLog(this->shaderProg, 1024, nullptr, buffer);
		std::cout << "LINK::ERROR::SHADER::PROGRAM" << std::endl;
		for (int i = 0; i < 1024; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
	}

	glDetachShader(this->shaderProg, vertexShader);
	glDetachShader(this->shaderProg, geometryShader);
	glDetachShader(this->shaderProg, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {

}

void Shader::use() {
	glUseProgram(this->shaderProg);
}
void Shader::setName(std::string name) {
	this->name = name;
}
std::string Shader::getName() const {
	return this->name;
}
//Set uniform matrix4x4
void Shader::setMat4(std::string name, glm::mat4 mat) {
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());
	if (uniformLoc != -1) {
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &mat[0][0]);
	}
	else {
		std::cout << "Uniform doesn't exist with name: " + name << std::endl;
	}
}
//Set uniform vector3
void Shader::setVec3(std::string name, glm::vec3 vec) {
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());
	if (uniformLoc != -1) {
		glUniform3fv(uniformLoc, 1, &vec[0]);
	}
	else {
		std::cout << "Uniform doesn't exist with name: " + name << std::endl;
	}
}
//Set uniform float
void Shader::setFloat(std::string name, float val) {
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());
	if (uniformLoc != -1) {
		glUniform1f(uniformLoc, val);
	}
	else {
		std::cout << "Uniform doesn't exist with name: " + name << std::endl;
	}
}
//Set uniform int
void Shader::setInt(std::string name, int val) {
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());
	if (uniformLoc != -1) {
		glUniform1i(uniformLoc, val);
	}
	else {
		std::cout << "Uniform doesn't exist with name: " + name << std::endl;
	}

}

unsigned int Shader::getShaderID() const {
	return this->shaderProg;
}