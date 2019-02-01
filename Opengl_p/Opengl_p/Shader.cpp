#include "Shader.h"

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

Shader::~Shader() {

}

void Shader::use() {
	glUseProgram(this->shaderProg);
}

void Shader::setMat4(std::string name, glm::mat4 mat) {
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());
	if (uniformLoc != -1) {
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &mat[0][0]);
	}
}

void Shader::setVec3(std::string name, glm::vec3 vec) {
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());
	if (uniformLoc != -1) {
		glUniform3fv(uniformLoc, 1, &vec[0]);
	}
}

void Shader::setFloat(std::string name, float val) {
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());
	if (uniformLoc != -1) {
		glUniform1f(uniformLoc, val);
	}
}

unsigned int Shader::getShaderID() const {
	return this->shaderProg;
}