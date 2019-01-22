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
		
		fileloader.loadObj(path, this->vertices, this->uvs, this->normals, this->triangles, this->orderedVerts);
	}
	else {
		printf("%s\n", "Filetype not supported");
	}


}


int Object::getByteSize() {
	//this only looks at the byte size relation with the number of triangles
	return sizeof(glm::vec3) * this->triangles.size() * 3;
}

std::vector<Vertex> Object::getOrderedVertices() const {
	return this->orderedVerts;
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
std::vector<Triangle> Object::getTriangles() const {
	return this->triangles;
}