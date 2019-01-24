#ifndef MATERIAL_h
#define MATERIAL_h
#include "Containers.h"
//Basic material for .mtl files
class Material {
public:
	
	Material() {
	
	};
	~Material() {
	
	};

	glm::vec3 ambientCol;
	glm::vec3 diffuseCol;
	glm::vec3 specularCol;
	float specularWeight;
	float transparency;
	std::string name;
	int illuminationModel;
	
};


#endif