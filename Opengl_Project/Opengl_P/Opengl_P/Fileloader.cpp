#include "Fileloader.h"

Fileloader::Fileloader() {
	//Setup the valid file types
	this->validFiletypes.push_back(".obj");

}

Fileloader::~Fileloader()
{
}

bool Fileloader::validType(std::string path) {
	std::list<char> temp;
	std::string extension;

	std::cout << "Path: " + path << std::endl;
	
	for (int i = path.length() - 1; i > 0; i--) {
		extension.push_back(path.at(i));

		//temp.push_front(path.at(i));
		if (path.at(i) == '.') {
			break;
		}
	}
	std::cout << extension << std::endl;
	std::string correct;
	for (int i = 0; i < extension.length(); i++) {
		correct.push_back(extension.at(extension.length() - i - 1));
	}
	std::cout << correct << std::endl;

	for (int i = 0; i < validFiletypes.size(); i++) {
		if (validFiletypes.at(i) == correct) {
			return true;
		}
	}
	return false;
}

void Fileloader::loadFile(std::string path) {
	if (this->validType(path)) {
		std::cout << "Path is valid" << std::endl;
	}
}
