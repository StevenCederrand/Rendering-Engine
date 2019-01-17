#ifndef OBJECT_h
#define OBJECT_h

#include "Containers.h"
#include "Fileloader.h"
#include <vector>

//3D Object class
class Object {
public:
	Object();
	Object(std::string path);
	~Object();
	
	void loadModel(std::string path);
	
	std::vector<Color> getColors() const;
	std::vector<UV> getUV() const;
	std::vector<glm::vec3> getNormals() const;
	std::vector<Vertex> getVertices() const;

private:

	


	std::vector<Color> colors;
	std::vector<UV> uvs;
	std::vector<glm::vec3> normals;
	std::vector<Vertex> vertices;
	
	
};


#endif