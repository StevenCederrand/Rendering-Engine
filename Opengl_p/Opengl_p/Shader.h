#ifndef SHADER_h
#define SHADER_h

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Containers.h"

class Shader {
public:
	//Input vertex path & fragment path
	Shader(std::string vPath, std::string fPath);
	~Shader();

	void use();

	void setMat4(std::string name, glm::mat4 mat);
	void setVec3(std::string name, glm::vec3 vec);
	void setFloat(std::string name, float val);
	unsigned int getShaderID() const;

private: 
	unsigned int shaderProg;
};

#endif