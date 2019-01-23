#ifndef SHADER_h
#define SHADER_h

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	//Input vertex path & fragment path
	Shader(std::string vPath, std::string fPath);
	~Shader();

	void use();
	unsigned int getShaderID() const;

private: 
	unsigned int shaderProg;
};

#endif