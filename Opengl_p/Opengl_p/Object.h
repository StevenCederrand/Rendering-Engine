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
	
	Mesh getMesh() const;
	Texture getTexture(Texturetypes type);

	Material getMaterial() const;
	
	void setMesh(Mesh mesh);
	void setMaterial(Material material);
	void caluclateTangentBasis();

	Object& operator=(const Object &other);

	std::vector<glm::vec3> v; //Vertices
	std::vector<glm::vec3> n; //Normals
	std::vector<glm::vec2> uv; //uvs

private:
	Material material;
	Mesh mesh;
	
};

#endif