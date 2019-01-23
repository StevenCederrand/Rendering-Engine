#ifndef OBJECT_h
#define OBJECT_h

#include "Containers.h"
#include "Material.h"
#include <vector>

//3D Object class
class Object {
public:
	Object();
	~Object();
	
	std::vector<UV> getUV() const;
	std::vector<Vertex> getNormals() const;
	std::vector<Vertex> getVertices() const;
	std::vector<Triangle> getTriangles() const;
	std::vector<Vertex> getOrderedVertices() const;


	void setUV(std::vector<UV> uv);
	void setNormals(std::vector<Vertex> normals);
	void setVertices(std::vector<Vertex> verts);
	void setTriangles(std::vector<Triangle> triangles);
	void setOrderedVertices(std::vector<Vertex> orderedVerts);

	//Get the size of the object	
	int getByteSize();

private:
	Material* material;

	std::vector<Vertex> orderedVerts;
	std::vector<UV> uvs;
	std::vector<Vertex> normals;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
};


#endif