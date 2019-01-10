#include "Fileloader.h"

Fileloader::Fileloader() {
	//Setup the valid file types
	this->validFiletypes.push_back(".obj");

}

Fileloader::~Fileloader()
{
}


std::string Fileloader::getExtension(std::string path) {
	std::list<char> temp;
	std::string extension;

	std::cout << "Path: " + path << std::endl;

	for (int i = path.length() - 1; i > 0; i--) {
		extension.push_back(path.at(i));

		if (path.at(i) == '.') {
			break;
		}
	}
	std::cout << extension << std::endl;
	std::string correct;
	for (int i = 0; i < extension.length(); i++) {
		correct.push_back(extension.at(extension.length() - i - 1));
	}

}

void Fileloader::loadFile(std::string path) {
	std::string extension = this->getExtension(path);
	bool validExtension = false;
	//Check extension validity
	for (int i = 0; i < validFiletypes.size() && validExtension == false; i++) {
		if (validFiletypes.at(i) == extension) {
			validExtension = true;
		}
	}
	if(validExtension) { 
		if (extension == ".obj") {

		}
	}
}
