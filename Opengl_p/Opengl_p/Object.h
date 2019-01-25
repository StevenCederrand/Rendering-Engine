#ifndef OBJECT_h
#define OBJECT_h

#include "Containers.h"
#include "Shader.h"

#include <vector>

//3D Object class
class Object {
public:
	Object();
	Object(const Object& other);
	~Object();
	
	void useShader();

	std::vector<UV> getUV() const;
	std::vector<Vertex> getNormals() const;
	std::vector<Vertex> getVertices() const;
	std::vector<Triangle> getTriangles() const;
	std::vector<Vertex> getOrderedVertices() const;
	
	Material* getMaterial() const;
		
	void setUV(std::vector<UV> uv);
	void setNormals(std::vector<Vertex> normals);
	void setVertices(std::vector<Vertex> verts);
	void setTriangles(std::vector<Triangle> triangles);
	void setOrderedVertices(std::vector<Vertex> orderedVerts);
	void setMaterial(Material* material);

	//Get the size of the object	
	int getByteSize();


	Object& operator=(const Object &other);
private:
	Material* material;

	std::vector<Vertex> orderedVerts;
	std::vector<UV> uvs;
	std::vector<Vertex> normals;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
};


#endif