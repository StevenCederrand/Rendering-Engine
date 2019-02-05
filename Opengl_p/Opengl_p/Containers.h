
/*
Simple container file. Used to contain general enums that may be/are used in the program
-Steven Cederrand
*/

#ifndef	CONTAINERS_h
#define CONTAINERS_h
#include <string>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <vector>
const std::string OBJECTSPATH = "..\\..\\Objects\\";
const std::string SHADERPATH = "..\\..\\Shader\\";

enum Texturetypes {
	Diffuse, 
	Normal, 
};

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
enum ValidKeys {
	W,
	S,
	A,
	D,
	Q, 
	E,
	ESC,
	DUMMY
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
//Struct of functions that make rotations a lot more conveniant --- the struct can be removed. But we may find it a little bit more comfortable.
struct Rotations {
	//Get the rotation matrix of a specific angle(Converts the angle into radians)
	void getXRotationAtAngle(float angle, glm::mat4& cMat) {
		angle = glm::radians(angle);

		float sinVal = glm::sin(angle);
		float cosVal = glm::cos(angle);
		cMat = glm::mat4(glm::vec4(1, 0, 0, 0),
						 glm::vec4(0, cosVal, -sinVal, 0),
						 glm::vec4(0, sinVal, cosVal, 0),
						 glm::vec4(0, 0, 0, 1));
	}

	//Get the rotation matrix of a specific angle(Converts the angle into radians)
	void getYRotationAtAngle(float angle, glm::mat4& cMat) {
		angle = glm::radians(angle);

		float sinVal = glm::sin(angle);
		float cosVal = glm::cos(angle);
		cMat = glm::mat4(
			glm::vec4(cosVal, 0, -sinVal, 0), 
			glm::vec4(0, 1, 0, 0), 
			glm::vec4(sinVal, 0, cosVal, 0), 
			glm::vec4(0, 0, 0, 1));
	}

	//Get the rotation matrix of a specific angle(Converts the angle into radians)
	void getZRotationAtAngle(float angle, glm::mat4& cMat) {
		angle = glm::radians(angle);

		float sinVal = glm::sin(angle);
		float cosVal = glm::cos(angle);
		cMat = glm::mat4(
			glm::vec4(cosVal, -sinVal, 0, 0),
			glm::vec4(sinVal, cosVal, 0, 0),
			glm::vec4(0, 0, 1, 0),
			glm::vec4(0, 0, 0, 1));
	}
};

#endif