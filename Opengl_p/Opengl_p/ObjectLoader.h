#ifndef OBJECTLOADER_h
#define OBJECTLOADER_h
#include "Object.h"

class ObjectLoader {
public:
	ObjectLoader();
	~ObjectLoader();
	
	void loadObject(Object obj, Shader* shader);
	int getNumberOfVAOs() const;
	int getNumberOfVBOs() const;

	std::vector<GLuint> getVAOs() const;
	std::vector<GLuint> getVBOs() const;

	void bindVAO(int at);
	void bindVBO(int at);

	void unbindVAO();
	void unbindVBO();

	void clean();
private:
	void genVAO();
	void genVBO();
	void attributePointers(int attributeLocation, int nrOfValues, int stride, int size);

	std::vector<GLuint> VBOs;
	std::vector<GLuint> VAOs;
	std::vector<GLuint> textures;
};

#endif