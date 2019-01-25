#include "Object.h"


Object::Object() {

}

Object::Object(const Object& other) {
	//Self-assignment check
	if (this != &other) {
		this->material = new Material(*other.getMaterial());
		this->setOrderedVertices(other.getOrderedVertices());
		this->setNormals(other.getNormals());
		this->setUV(other.getUV());
		this->setTriangles(other.getTriangles());
		this->setVertices(other.getVertices());
	}


}

Object::~Object() {
	delete this->material;
}


void Object::useShader() {

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

Material* Object::getMaterial() const {
	return this->material;
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

void Object::setMaterial(Material* material) {
	this->material = new Material(*material);
}



Object& Object::operator=(const Object &other) {
	//Self-assignment check
	if (this != &other) {
		this->material = new Material(*other.getMaterial());
		this->setOrderedVertices(other.getOrderedVertices());
		this->setNormals(other.getNormals());
		this->setUV(other.getUV());
		this->setTriangles(other.getTriangles());
		this->setVertices(other.getVertices());
	}


	return *this;
}