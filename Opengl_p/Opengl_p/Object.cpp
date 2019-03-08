#include "Object.h"

//#define STB_IMAGE_IMPLEMENTATION not using this because 
//it's already defined in fileloader.h
#include "stb_image.h"

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
		this->modelMatrix = other.modelMatrix;
		this->type = other.type;
		this->name = other.name;
		this->position = other.position;
		this->pointLight = other.pointLight;
		this->VAO = other.VAO;
		this->VBO = other.VBO;
	}
}

Object::~Object() {

}

void Object::calculateTangentBasis() {
	for (size_t i = 0; i < this->mesh.verts.size(); i+= 3) {
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
	for (size_t i = 0; i < this->material.textures.size(); i++) {
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
	this->mesh = Mesh(mesh);
}

void Object::setMaterial(Material material) {
	this->material = material;
}

void Object::destroyLight() {
	delete this->pointLight;
}

void Object::setPosition(glm::vec3 position) {
	this->position = position;
	this->modelMatrix = glm::translate(this->position);
}

glm::vec3 Object::getPosition() const {
	return this->position;
}

void Object::init() {
	//create & bind
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	
	int memorySize = this->mesh.verts.size() * sizeof(Vertex);

	glBufferData(GL_ARRAY_BUFFER, memorySize, &this->mesh.verts[0], GL_STATIC_DRAW);
	//Align buffer data
	this->attributePointers(0, 3, 8, 0);
	this->attributePointers(1, 3, 8, sizeof(glm::vec3));
	this->attributePointers(2, 2, 8, sizeof(float) * 6);

	//unbind the VAO & VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	std::cout << "Init complete" << std::endl;
	//this->loadTextures();
}

void Object::bind() {
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void Object::unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Bind-Draw-Unbind
void Object::draw(Shader* drawShader) {
	//drawShader->use();
	//drawShader->setInt("colorTexture", 0);
	//drawShader->setInt("normalMap", 1);

	for (size_t i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, this->textures.at(i));
	}

	this->bind();
	glDrawArrays(GL_TRIANGLES, 0, this->mesh.verts.size());
	this->unbind();
}

void Object::attributePointers(int attributeLocation, int nrOfValues, int stride, int size) {
	if (attributeLocation == -1) {
		std::cout << "ERROR::CAN'T::PROCESS::NEGATIVE::ATTRIBLOCATION" << std::endl;
		return;
	}
	glVertexAttribPointer(attributeLocation, nrOfValues, GL_FLOAT, GL_FALSE, sizeof(float)*stride, BUFFER_OFFSET(size));
	glEnableVertexAttribArray(attributeLocation);
}

Object& Object::operator=(const Object &other) {
	//Self-assignment check
	if (this != &other) {
		this->mesh = Mesh(other.mesh);
		this->material = other.getMaterial();
		this->v = other.v;
		this->n = other.n;
		this->uv = other.uv;
		this->modelMatrix = other.modelMatrix;
		this->type = other.type;
		this->name = other.name;
		this->position = other.position;
		this->pointLight = other.pointLight;
		this->VAO = other.VAO;
		this->VBO = other.VBO;

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

void Object::loadTextures() {
	for (size_t i = 0; i < this->material.textures.size(); i++) {
		unsigned int tex;
		//Load the diffuse texture
		if (i == 0) {
			this->setupTextures(tex, this->getTexture(Texturetypes::Diffuse).name);
		}
		else if (i == 1) {
			this->setupTextures(tex, this->getTexture(Texturetypes::Normal).name);
		}
		//After setting up the texture push it into the array of textures
		this->textures.push_back(tex);
	}
}

//Load the textures
void Object::setupTextures(unsigned int& texture, std::string name) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	std::string path = OBJECTSPATH + name;

	int width, height, nrChannels;

	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "GENERATED::TEXTURE" << std::endl;
	}
	else {
		std::cout << "ERROR::LOADING::TEXTURE" << std::endl;
	}
	stbi_image_free(data);
}