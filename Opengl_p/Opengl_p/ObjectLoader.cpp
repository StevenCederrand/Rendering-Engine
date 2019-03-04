#include "ObjectLoader.h"

ObjectLoader::ObjectLoader() {
}

ObjectLoader::~ObjectLoader() {

}

void ObjectLoader::loadObject(Object obj, Shader* shader) {
	this->genVAO();
	this->genVBO();

	
	std::vector<Vertex> meshData = obj.getMesh().verts;
	int memorySize = meshData.size() * sizeof(Vertex);
	
	glBufferData(GL_ARRAY_BUFFER, memorySize, &meshData[0], GL_STATIC_DRAW);

	//Setup data going into the shader -> See comment at the bottom of the page if in need of details
	this->attributePointers(0, 3, 8, 0);
	this->attributePointers(1, 3, 8, sizeof(glm::vec3));
	this->attributePointers(2, 2, 8, sizeof(float) * 6);
	
	this->unbindVAO();
	this->unbindVBO();
}

void ObjectLoader::attributePointers(int attributeLocation, int nrOfValues, int stride, int size) {
	if (attributeLocation == -1) {
		std::cout << "ERROR::CAN'T::PROCESS::NEGATIVE::ATTRIBLOCATION" << std::endl;
		return;
	}
	glVertexAttribPointer(attributeLocation, nrOfValues, GL_FLOAT, GL_FALSE, sizeof(float)*stride, BUFFER_OFFSET(size));
	glEnableVertexAttribArray(attributeLocation);

}

void ObjectLoader::clean() {
	for (int i = 0; i < this->VBOs.size(); i++) {
		glDeleteBuffers(1, &this->VBOs.at(i));
		glDeleteVertexArrays(1, &this->VAOs.at(i));
	}
	
}
int ObjectLoader::getNumberOfVAOs() const {
	return this->VAOs.size();
}

int ObjectLoader::getNumberOfVBOs() const {
	return this->VBOs.size();
}

std::vector<unsigned int> ObjectLoader::getVAOs() const {
	return this->VAOs;
}

std::vector<unsigned int> ObjectLoader::getVBOs() const {
	return this->VBOs;
}

void ObjectLoader::bindVAO(int at) {
	glBindVertexArray(this->VAOs.at(at));
}

void ObjectLoader::unbindVAO() {
	glBindVertexArray(0);
}

void ObjectLoader::bindVBO(int at) {
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOs.at(at));
}

void ObjectLoader::unbindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Generate a VAO
void ObjectLoader::genVAO() {
	GLuint tempVAO;
	glGenVertexArrays(1, &tempVAO);
	glBindVertexArray(tempVAO);
	VAOs.push_back(tempVAO);
}

//Generate a VBO
void ObjectLoader::genVBO() {
	GLuint tempVBO;
	glGenBuffers(1, &tempVBO);
	glBindBuffer(GL_ARRAY_BUFFER, tempVBO);

	this->VBOs.push_back(tempVBO);
}



/*

	GLint attributeLocation = 0;
	if (attributeLocation == -1) {
		std::cout << "ERROR::LOCATING::VERTEX::POS" << std::endl;
		return;
	}

	//Set the vertices in the glsl-code
	glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	//Load normals
	attributeLocation = 1;
	if (attributeLocation == -1) {
		std::cout << "ERROR::LOCATING::NORMAL::POS" << std::endl;
		return;
	}
	glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(glm::vec3)));
	glEnableVertexAttribArray(attributeLocation);

	//Load uv's
	attributeLocation = 2;
	if (attributeLocation == -1) {
		std::cout << "ERROR::LOCATING::UV::POS" << std::endl;
		return;
	}
	glVertexAttribPointer(attributeLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(float) * 6));
	glEnableVertexAttribArray(attributeLocation);

*/