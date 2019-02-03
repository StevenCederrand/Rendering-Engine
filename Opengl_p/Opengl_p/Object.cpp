#include "Object.h"


Object::Object() {
	this->mesh = Mesh();
}

Object::Object(const Object& other) {
	//Self-assignment check
	if (this != &other) {
		this->mesh = Mesh(other.mesh);
		this->material = other.getMaterial();

		this->v = other.v;
		this->n = other.n;
		this->uv = other.uv;
	}


}

Object::~Object() {

}

Texture Object::getTexture(Texturetypes type) {
	Texture texture;
	for (int i = 0; i < this->material.textures.size(); i++) {
		if (this->material.textures.at(i).type == type) {
			texture = this->material.textures.at(i);
			break;
		}
	}
	return texture;
}

Mesh Object::getMesh() const {
	return this->mesh;
}

Material Object::getMaterial() const {
	return this->material;
}

void Object::setMesh(Mesh mesh) {
	//delete this->mesh; //Could be a problem
	this->mesh = Mesh(mesh);
}

void Object::setMaterial(Material material) {
	this->material = material;//Material(material);
}

Object& Object::operator=(const Object &other) {
	//Self-assignment check
	if (this != &other) {
		this->mesh = Mesh(other.mesh);
		this->material = other.getMaterial();//Material(*other.getMaterial());
		this->v = other.v;
		this->n = other.n;
		this->uv = other.uv;
	}


	return *this;
}