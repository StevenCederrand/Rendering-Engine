#ifndef SHADERMANAGER_h
#define SHADERMANAGER_h
#include "Shader.h"
#include <vector>

class ShaderManager {
public: 
	ShaderManager();
	~ShaderManager();

	Shader* insertShader(std::string vPath, std::string fPath, std::string name);
	//Returns the adress of the new shader
	Shader* insertShader(std::string vPath, std::string gPath, std::string fPath, std::string name);

	std::vector<Shader*> getShaders() const;
	//Get a shader by name
	Shader* getSpecific(std::string name) const;

private:
	std::vector<Shader*> shaders;
};


#endif