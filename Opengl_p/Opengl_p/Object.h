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
	
	//Get functions
	Mesh getMesh() const;
	Texture getTexture(Texturetypes type);
	Material getMaterial() const;
	glm::vec3 getPosition() const;

	//Set functions
	//Automatically translates the model matrix
	void setPosition(glm::vec3 position);
	void setMesh(Mesh mesh);
	void setMaterial(Material material);

	
	void assignMaterial(Shader* shader);
	void calculateTangentBasis();
	void destroyLight();
	void draw(Shader* drawShader);
	void init();


	Object& operator=(const Object &other);

	//Variables
public:
	std::vector<glm::vec3> v; //Vertices
	std::vector<glm::vec3> n; //Normals
	std::vector<glm::vec2> uv; //uvs

	glm::mat4 modelMatrix = glm::mat4(1.f);

	ObjectTypes type;
	std::string name; 

	PointLight* pointLight;	
private:
	Material material;
	Mesh mesh;

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	glm::vec3 position = glm::vec3(0, 0, 0);

	//Functions related to drawing 
	void bind();
	void unbind();
	void attributePointers(int attributeLocation, 
		int nrOfValues, 
		int stride, 
		int size);

	unsigned int VAO;
	unsigned int VBO;	


	//Textures
	void loadTextures();
	void setupTextures(unsigned int& texture, 
		std::string name);

	//These textures should be loaded into memory
	std::vector<unsigned int> textures;
};


#endif