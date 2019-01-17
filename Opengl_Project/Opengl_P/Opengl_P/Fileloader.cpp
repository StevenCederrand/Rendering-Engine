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
	return correct;

}

void Fileloader::loadObj(std::string path, std::vector<Color>& color, std::vector<Vertex>& vertices, std::vector<UV>& uv, std::vector<glm::vec3>& normals) {

	std::fstream file;
	file.open(path.c_str(), std::ios::in);

	if (!file.is_open()) {
		printf("%s%s\n", "Couldn't open the file at path: ", path);
		return;
	}
	else {
		printf("%s\n", "File found and opened");
	}
	std::string line;
	uint8_t nrOfLines = 0;
	while (std::getline(file, line)) {
		
		
		nrOfLines++;
	}
	printf("%s%d\n", "Number of lines: ", nrOfLines);


	file.close();
}
