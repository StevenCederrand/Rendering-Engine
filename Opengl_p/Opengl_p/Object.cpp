#include "Object.h"


Object::Object() {

}

Object::~Object() {

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

void Object::setUV(std::vector<UV> uv) {
	this->uvs = uv;
}

void Object::setNormals(std::vector<Vertex> normals) {
	this->normals = normals;
}

void Object::setVertices(std::vector<Vertex> verts) {
	this->vertices = verts;
}

void Object::setTriangles(std::vector<Triangle> triangles) {
	this->triangles = triangles;
}

void Object::setOrderedVertices(std::vector<Vertex> orderedVerts) {
	this->orderedVerts = orderedVerts;
}
