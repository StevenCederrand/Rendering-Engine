
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

struct Vertex {
	glm::vec3 vertex;
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