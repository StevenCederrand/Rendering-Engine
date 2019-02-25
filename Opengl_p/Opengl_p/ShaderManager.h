#ifndef SHADERMANAGER_h
#define SHADERMANAGER_h
#include "Shader.h"
#include <vector>

class ShaderManager {
public: 
	ShaderManager();
	~ShaderManager();

	void insertShader(std::string vPath, std::string fPath, std::string name);
	void insertShader(std::string vPath, std::string gPath, std::string fPath, std::string name);

	std::vector<Shader*> getShaders() const;
	//Get a shader by name
	Shader* getSpecific(std::string name) const;

private:
	std::vector<Shader*> shaders;
};


#endif