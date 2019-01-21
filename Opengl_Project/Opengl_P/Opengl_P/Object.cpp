#include "Object.h"


Object::Object() {

}

//Initialize properties
Object::Object(std::string path) {
	this->loadModel(path);
	
}

Object::~Object() {

}

void Object::loadModel(std::string path) {
	Fileloader fileloader;
	
	if (fileloader.getExtension(path) == ".obj") {
		
		fileloader.loadObj(path, this->triangles);
	}
	else {
		printf("%s\n", "Filetype not supported");
	}


}


std::vector<Color> Object::getColors() const {
	return this->colors;
}
std::vector<UV> Object::getUV() const {
	return this->uvs;
}
std::vector<Vertex> Object::getNormals() const {
	return this->normals;
}
std::vector<Vertex> Object::getVertices() const {
	return this->vertices;
}