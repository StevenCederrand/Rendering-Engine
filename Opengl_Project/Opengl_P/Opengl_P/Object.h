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
	//Automatically load the data from a file into the object. 
	void loadModel(std::string path);
	
	std::vector<Color> getColors() const;
	std::vector<UV> getUV() const;
	std::vector<Vertex> getNormals() const;
	std::vector<Vertex> getVertices() const;
	std::vector<Triangle> getTriangles() const;
	//Get the size of the object
	int getByteSize();
private:
	std::vector<Color> colors;
	std::vector<UV> uvs;
	std::vector<Vertex> normals;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
};


#endif