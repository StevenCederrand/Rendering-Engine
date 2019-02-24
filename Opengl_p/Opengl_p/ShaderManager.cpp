#include "ShaderManager.h"

ShaderManager::ShaderManager() {
}

ShaderManager::~ShaderManager() {
	for (int i = 0; i < this->shaders.size(); i++) {
		delete this->shaders.at(i);
	}
}

void ShaderManager::insertShader(std::string vPath, std::string fPath, std::string name) {
	Shader* newShader = new Shader(vPath, fPath);
	newShader->setName(name);
	this->shaders.push_back(newShader);
}

void ShaderManager::insertShader(std::string vPath, std::string gPath, std::string fPath, std::string name) {
	Shader* newShader = new Shader(vPath, gPath, fPath);
	newShader->setName(name);
	this->shaders.push_back(newShader);
}

std::vector<Shader*> ShaderManager::getShaders() const {
	return this->shaders;
}

Shader* ShaderManager::getSpecific(std::string name) const {
	Shader* shader;
	for (int i = 0; i < this->shaders.size(); i++) {
		if (this->shaders.at(i)->getName() == name) {
			return this->shaders.at(i);
		}
	}

	return nullptr;
}
