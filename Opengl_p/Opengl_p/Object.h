#ifndef OBJECT_h
#define OBJECT_h

#include "Containers.h"
#include <vector>
#include "Shader.h"
//3D Object class
class Object {
public:
	Object();
	Object(const Object& other);
	~Object();
	
	Mesh getMesh() const;
	Texture getTexture(Texturetypes type);

	Material getMaterial() const;
	void calculateTangentBasis();
	void setMesh(Mesh mesh);
	void setMaterial(Material material);
	

	Object& operator=(const Object &other);

	std::vector<glm::vec3> v; //Vertices
	std::vector<glm::vec3> n; //Normals
	std::vector<glm::vec2> uv; //uvs

	void assignMaterial(Shader* shader);

	glm::mat4 modelMatrix = glm::mat4(1.f);
	glm::vec3 position = glm::vec3(0, 0, 0);
	
	ObjectTypes type;
	std::string name; 

	PointLight* pointLight;

private:
	Material material;
	Mesh mesh;

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;


	
};

#endif