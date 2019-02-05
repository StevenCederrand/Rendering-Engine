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

void Object::calculateTangentBasis() {
	for (int i = 0; i < this->mesh.verts.size(); i+= 3) {
		//Quickaccess to positions
		glm::vec3 position0 = this->mesh.verts.at(i).position;
		glm::vec3 position1 = this->mesh.verts.at(i + 1).position;
		glm::vec3 position2 = this->mesh.verts.at(i + 2).position;
		//Quickaccess to uv's
		glm::vec2 uv0 = this->mesh.verts.at(i).uv;
		glm::vec2 uv1 = this->mesh.verts.at(i+1).uv;
		glm::vec2 uv2 = this->mesh.verts.at(i+2).uv;

		//Triangle edge positions
		glm::vec3 edge0 = position1 - position0;
		glm::vec3 edge1 = position2 - position0;

		//UV delta
		glm::vec2 deltaUV0 = uv1 - uv0;
		glm::vec2 deltaUV1 = uv2 - uv0;

		//Compute tangent and bitangent
		float r = 1 / (deltaUV0.x * deltaUV1.x - deltaUV0.y * deltaUV1.y);
		glm::vec3 tangent = (edge0 * deltaUV1.y - edge1 * deltaUV0.y) * r;
		tangent = glm::normalize(tangent);

		glm::vec3 bitangent = (edge1 * deltaUV0.x - edge0 * deltaUV1.x) * r;
		bitangent = glm::normalize(bitangent); 
		
		//Same tangent for all three positions
		this->tangents.push_back(tangent);
		this->tangents.push_back(tangent);
		this->tangents.push_back(tangent);
		//Same bitangent for all three positions
		this->bitangents.push_back(bitangent);
		this->bitangents.push_back(bitangent);
		this->bitangents.push_back(bitangent);
	}
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

void Object::assignMaterial(Shader* shader) {
	shader->setVec3("ambientCol", this->getMaterial().ambientCol);
	shader->setVec3("diffuseCol", this->getMaterial().diffuseCol);
	shader->setVec3("specCol", this->getMaterial().specularCol);
	shader->setFloat("transparency", this->getMaterial().transparency);
	shader->setFloat("specularWeight", this->getMaterial().specularWeight);
}