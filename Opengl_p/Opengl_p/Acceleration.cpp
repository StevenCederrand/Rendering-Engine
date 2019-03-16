#include "Acceleration.h"


Acceleration::Acceleration() {

}


Acceleration::~Acceleration() {

}

//Sort the objects in the scene based on their distance to the camera
void Acceleration::frontBackRendering(std::vector<Object>& sceneObjects, glm::vec3 cameraPos) {

	std::vector<Data> distances;
	//Order Check
	if (this->orderCheck(sceneObjects, cameraPos)) {
		return;
	}
	else {
		std::cout << "Objects are not in order" << std::endl;
	}

	//Insert all of the relevant data to the distance array
	for (size_t i = 0; i < sceneObjects.size(); i++) {
		glm::vec3 objToCam = sceneObjects.at(i).getPosition() - cameraPos;
		float distance = glm::dot(objToCam, objToCam); //get quadratic distance
		distances.push_back(Data(distance, i));
	}

	this->quickSort(distances, 0, distances.size() - 1);
	std::vector<Object> sortedObjs;

	for (size_t i = 0; i < sceneObjects.size(); i++) {
		sortedObjs.push_back(sceneObjects.at(distances.at(i).tag));
	}

	sceneObjects = sortedObjs;
}


void Acceleration::quickSort(std::vector<Data>& data, int left, int right) {

	int i, j, mid;
	Data piv;
	i = left;
	j = right;
	mid = left + (right - left) / 2;
	piv = data.at(mid);

	while (i < right || j > left) {
		while (data.at(i).distance < piv.distance)
			i++;
		while (data.at(j).distance > piv.distance)
			j--;

		if (i <= j) {
			this->swap(data, i, j); 
			i++;
			j--;
		}
		else {
			if (i < right)
				quickSort(data, i, right);
			if (j > left)
				quickSort(data, left, j);
			return;
		}
	}
}

bool Acceleration::orderCheck(std::vector<Object> sceneObjects, glm::vec3 cameraPos) {
	bool inOrder = true;

	for (size_t i = 0; i < sceneObjects.size() - 1 && inOrder; i++) {
		glm::vec3 objToCam = sceneObjects.at(i).getPosition() - cameraPos;
		glm::vec3 nObjToCam = sceneObjects.at(++i).getPosition() - cameraPos;

		float distanceA = glm::dot(objToCam, objToCam);
		float distanceB = glm::dot(nObjToCam, nObjToCam);

		if (distanceA > distanceB) {
			inOrder = false;
		}
	}
	return inOrder;
}

//Swap the data around
void Acceleration::swap(std::vector<Data> &data, int from, int to) {
	Data tmp = data.at(from);
	data.at(from) = data.at(to);
	data.at(to) = tmp;
}

void Acceleration::test(std::vector<glm::vec3>& positions, glm::vec3 cameraPos) {
	std::vector<Data> distances;
	
	//Insert all of the relevant data to the distance array
	for (size_t i = 0; i < positions.size(); i++) {
		glm::vec3 objToCam = positions.at(i) - cameraPos;
		float distance = glm::dot(objToCam, objToCam); //get quadratic distance
		distances.push_back(Data(distance, i));
	}
	
	//std::cout << "Pre sort" << std::endl;
	//for (int i = 0; i < distances.size(); i++) {
	//	std::cout << distances.at(i).tag;
	//	std::cout << " : ";
	//	std::cout << distances.at(i).distance << std::endl;
	//}

	this->quickSort(distances, 0, distances.size() - 1);

	//std::cout << "Post sort" << std::endl;
	//for (int i = 0; i < distances.size(); i++) {
	//	std::cout << distances.at(i).tag;
	//	std::cout << " : ";
	//	std::cout << distances.at(i).distance << std::endl;
	//}

	std::vector<glm::vec3> newPositions;

	std::cout << "Positions \n";
	for (size_t i = 0; i < positions.size(); i++) {
		newPositions.push_back(positions.at(distances.at(i).tag));
	}

	positions = newPositions;
}

