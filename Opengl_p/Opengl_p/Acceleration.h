#ifndef ACCELERATION_h
#define ACCELERATION_h
#include "Object.h"

struct Data {
	Data() {

	}
	Data(float distance, int tag) {
		this->distance = distance;
		this->tag = tag;
	}

	float distance;
	int tag; //What object does this data correspond with
};

//Class containing different acceleration Techniques
class Acceleration {
public:

	Acceleration();
	~Acceleration();
	//Sort the objects in the scene based on their distance to the camera
	void frontBackRendering(std::vector<Object>& sceneObjects, glm::vec3 cameraPos);
	//Remove this function later on
	void test(std::vector<glm::vec3>& positions, glm::vec3 cameraPos);

	//Quicksort is not a great algorithm choice because it is inefficiant when 
	//the data that needs sorting has only minor sorting issues
	void quickSort(std::vector<Data> &data, int left, int right);
private: 
	bool orderCheck(std::vector<Object> sceneObjects, glm::vec3 cameraPos);
	//Swap data from left to right
	void swap(std::vector<Data> &data, int from, int to);

};

#endif