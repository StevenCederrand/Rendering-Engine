#ifndef FILELOADER_h
#define FILELOADER_h

#include "Containers.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <list>

/* Fileloader. This may parse data of certain filetypes. */
class Fileloader {
public:
	Fileloader();
	~Fileloader();

	void loadObj(std::string path, std::vector<Color> &color, std::vector<Vertex> &vertices, 
		std::vector<UV> &uv, std::vector<Vertex> &normals);
	
	std::string getExtension(std::string path);
	//Private functions
private:

	//Private variables
private:
	std::vector<std::string> validFiletypes;
};


#endif