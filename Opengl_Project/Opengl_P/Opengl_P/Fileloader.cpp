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

void Fileloader::loadObj(std::string path, std::vector<Color>& color, std::vector<Vertex>& vertices, std::vector<UV>& uv, std::vector<Vertex>& normals) {

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
	int nrOfLines = 0;
	int nrOfVerts = 0;
	int nrOfUV = 0;
	int nrOfNormals = 0;
	while (std::getline(file, line)) {
		if (line[0] == 'v' ) {
			std::string val = line;
			std::cout << val << std::endl;

			//Get each vertex position
			if (line[1] == ' ') {
				Vertex vert = Vertex();
				std::string val = "";

				//Read the line
				for (int i = 2; i < line.length(); i++) {
					if (line[i] == ' ' || i == line.length() - 1) {
						//Set the vertex x, y, z
						vert.vertex[vert.occupied] = std::stof(val);
						vert.occupied++;

						val = "";
					}
					else {
						val += line[i];
					}
				}
				//Save the vertex to the vertex vector
				vertices.push_back(vert);
				nrOfVerts++;
			}
			//If we're dealing with a vertex texture
			else if (line[1] == 't') {
				UV tempUV = UV();
				std::string val = "";
				for (int i = 3; i < line.length(); i++) {
					//Between each texture coordinate
					if (line[i] == ' ' || i == line.length() - 1) {
						//add a uv.x or y onto the UV struct
						tempUV.uv[tempUV.occupied] = std::stof(val);
						tempUV.occupied++;
						val = "";
					}
					else {
						val += line[i];
					}
				}
				//at the end of the line
				uv.push_back(tempUV);
				nrOfUV++;
			}
			//If we're dealing with vertex normals
			else if (line[1] == 'n') {
				Vertex tempNormal = Vertex();
				std::string val = "";
				for (int i = 3; i < line.length(); i++) {
					if (line[i] == ' ' || i == line.length() - 1) {
						//Set the tempNormal
						tempNormal.vertex[tempNormal.occupied] = std::stof(val);
						tempNormal.occupied++;
						val = "";
					}
					else {
						val += line[i];
					}
				}
				//At the end of line
				normals.push_back(tempNormal);
				nrOfNormals++;
			}
		}
		
		nrOfLines++;
	}

	printf("%s%d\n", "Number of lines: ", nrOfLines);
	printf("%s%d\n", "Number of vertices: ", nrOfVerts);
	printf("%s%d\n", "Number of UVs: ", nrOfUV);
	printf("%s%d\n", "Number of Normals: ", nrOfNormals);
	file.close();
}
