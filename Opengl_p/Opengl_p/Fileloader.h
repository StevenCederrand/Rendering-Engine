#ifndef FILELOADER_h
#define FILELOADER_h

#include "Object.h"
#include "Containers.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <list>
#include <string>

/* Fileloader. This may parse data of certain filetypes. */
class Fileloader {
public:
	Fileloader();
	~Fileloader();

	Object loadObj(std::string path);
	
	std::string getExtension(std::string path);

	//Private functions 
private:  
	Material* loadMaterial(std::string path);
	glm::vec3 extractVector(std::string line);
	//Private variables
private:
	std::vector<std::string> validFiletypes;
};


#endif