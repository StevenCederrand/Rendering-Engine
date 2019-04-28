
/*
Simple container file. Used to contain general enums that may be/are used in the program
-Steven Cederrand
*/

#ifndef	CONTAINERS_h
#define CONTAINERS_h
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

#include <string>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <vector>


const std::string OBJECTSPATH = "..\\..\\Objects\\";
const std::string SHADERPATH = "..\\..\\Shader\\";
#pragma region ENUMS
enum Texturetypes {
	Diffuse, 
	Normal, 
};

enum ValidKeys {
	W,
	S,
	A,
	D,
	Q, 
	E,
	ESC,
	DUMMY,
	I,
	J,
	K,
	L, 
	H, 
	LEFT_MOUSE_BUTTON,
};

enum ObjectTypes {
	Standard,
	HeightMapBased,
	LightSource,
};
#pragma endregion

struct Texture {
	Texturetypes type;
	std::string name;
	unsigned int texture; //Assigned when loading the texture into the texture buffer
	float textureStr;
};

//Each vertex should contain a tangent and bitangent? Look in deeper to normalmapping
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

struct Mesh {
	Mesh() {

	};
	Mesh(const Mesh& other) {
		this->verts = other.verts;
	}
	~Mesh() {
		
	};
	std::vector<Vertex> verts;
};

//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
struct TangentBasis {
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
};

static std::string vec3ToString(glm::vec3 vec) {
	std::string x = "X: " + std::to_string(vec.x) + " Y: " + std::to_string(vec.y) + " Z: " + std::to_string(vec.z) + "\n";
	return x;
};

struct Material {

	Material() {

	};

	Material(const Material &otherMat) {
		this->ambientCol = otherMat.ambientCol;
		this->diffuseCol = otherMat.diffuseCol;
		this->specularCol = otherMat.specularCol;
		this->illuminationModel = otherMat.illuminationModel;
		this->specularWeight = otherMat.specularWeight;
		this->transparency = otherMat.transparency;
		this->name = otherMat.name;
		this->textures = otherMat.textures;
	};

	~Material() {

	};

	glm::vec3 ambientCol;
	glm::vec3 diffuseCol;
	glm::vec3 specularCol;
	float specularWeight;
	float transparency;
	std::string name;
	int illuminationModel;
	std::vector<Texture> textures;

};

struct PointLight {
	PointLight& operator=(const PointLight& other) {
		if (this != &other) {
			this->factors = other.factors;
		}
	}
	glm::vec4 factors; //x = constant, y = linear, z = quadratic
};

#endif