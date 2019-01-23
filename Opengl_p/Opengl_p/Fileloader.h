#ifndef FILELOADER_h
#define FILELOADER_h

#include "Object.h"
#include "Containers.h"
#include "Material.h"

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

	void loadObj(std::string path, std::vector<Vertex> &vertices, 
		std::vector<UV> &uv, std::vector<Vertex> &normals, std::vector<Triangle> &triangles, 
		std::vector<Vertex> &orderedVerts, Material* material);
	Object loadObj(std::string path);
	
	//void loadMTL(std::string MTLPath, Material* material);
	std::string getExtension(std::string path);
	
	//Private variables
private:
	std::vector<std::string> validFiletypes;
};


#endif