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
	
	//void loadMap(std::string path, int width, int height, int bpp, int cpp); //cpp = components per pixel
	void loadMap(std::string path, int &width, int &height, std::vector<float> &elevation);
	Object readFile(std::string path);
	std::string getExtension(std::string path);

	//Private functions 
private:  
	Material loadMaterial(std::string path);
	glm::vec3 extractVector(std::string line);
	std::string split(std::string val, const char c);
	
	bool validExtension(std::string path);
	
	std::string splitAt(std::string path, int at);
	glm::vec3 interpretVec3(std::string line);
	glm::vec2 interpretVec2(std::string line);
	void interpretMesh(std::string line, Mesh &mesh, Object object);

	//Private variables
private:
	std::vector<std::string> validFiletypes;
};


#endif