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

void Fileloader::loadObj(std::string path, std::vector<Triangle>& triangles) {

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

	std::vector<UV> uv;
	std::vector<Vertex> normals;
	std::vector<Vertex> vertices;

	int nrOfLines = 0;
	int nrOfVerts = 0;
	int nrOfUV = 0;
	int nrOfNormals = 0;


	while (std::getline(file, line)) {
		if (line[0] == 'v') {

			//Get each vertex position
			if (line[1] == ' ') {
				//std::cout << line << std::endl;
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
		//Now we have to figure out a way to handle faces
		else if (line[0] == 'f') {
			std::string val = "";
			//Number of slashes passed
			uint8_t slashes = 0;


			Triangle tempTriangle = Triangle();
			for (int i = 1; i < line.length(); i++) {
				int x = 0;
				//When stumbling on spaces or at the end
				if (line[i] == '/' || line[i] == ' ' || i == line.length() - 1) {
					if (val != "") {
						switch (slashes) {
						case 0:
							//Push the vertex at pos val - 1 into the triangles list of verts
							//std::cout << val + " ";
							tempTriangle.vertices.push_back(vertices.at(std::stoi(val) - 1));
							break;
						case 1:
							tempTriangle.uvs.push_back(uv.at(std::stoi(val) - 1));
							//std::cout << val + " ";
							break;
						case 2:
							tempTriangle.normals.push_back(normals.at(std::stoi(val) - 1));
							//std::cout << val + " ";
							break;
						}

					}
					if (line[i] == '/') {
						slashes++;
						val = "";
					}

					if (line[i] == ' ' || i == line.length() - 1) {
						val += line[i];
						//std::cout << val << std::endl;

						//Ghetto fix for adding the last vn
						if (val != " ") {
							tempTriangle.normals.push_back(normals.at(std::stoi(val) - 1));
						}

						//std::cout << std::endl;
						val = "";
						slashes = 0;
					}
				}
				else {
					val += line[i];
				}
			}
			triangles.push_back(tempTriangle);

		}
		nrOfLines++;

	}
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
	Triangle tempTriangle = Triangle();
	while (std::getline(file, line)) {
		if (line[0] == 'v' ) {
			
			//Get each vertex position
			if (line[1] == ' ') {
				//std::cout << line << std::endl;
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
		//Now we have to figure out a way to handle faces
		else if (line[0] == 'f') {
			std::string val = "";
			//Number of slashes passed
			uint8_t slashes = 0;
			

			//std::cout << line << std::endl;
			for (int i = 1; i < line.length(); i++) {
				int x = 0;
				//When stumbling on spaces or at the end
				if (line[i] == '/' || line[i] == ' ' || i == line.length() - 1) {
					if (val != "") {
						switch (slashes) {
						case 0:
							//Push the vertex at pos val - 1 into the triangles list of verts
							//std::cout << val + " ";
							tempTriangle.vertices.push_back(vertices.at(std::stoi(val)-1));
							break;
						case 1:
							tempTriangle.uvs.push_back(uv.at(std::stoi(val) - 1));
							//std::cout << val + " ";
							break;
						case 2:
							tempTriangle.normals.push_back(normals.at(std::stoi(val) - 1));
							//std::cout << val + " ";
							break;
						}

					}
					if (line[i] == '/') {
						slashes++;
						val = "";
					}

					if (line[i] == ' ' ||i == line.length() - 1) {
						val += line[i];
						//std::cout << val << std::endl;
						
						//Ghetto fix for adding the last vn
						if (val != " ") {
							tempTriangle.normals.push_back(normals.at(std::stoi(val) - 1));
						}

						//std::cout << std::endl;
						val = "";
						slashes = 0;
					}
				}
				else {
					val += line[i];
				}
			}

		}
		nrOfLines++;
		
	}
	/*
	printf("%s%d\n", "Number of loaded Vertices: ", tempTriangle.vertices.size());
	for (int i = 0; i < tempTriangle.vertices.size(); i++) {

		if (i % 3 == 0) {
			std::cout << "New Triangle" << std::endl;
		}
		std::cout << tempTriangle.vertices.at(i).vertex.x;
		std::cout << " ";
		std::cout << tempTriangle.vertices.at(i).vertex.y;
		std::cout << " ";
		std::cout << tempTriangle.vertices.at(i).vertex.z << std::endl;
	}


	printf("%s%d\n", "Number of lines: ", nrOfLines);
	printf("%s%d\n", "Number of vertices: ", nrOfVerts);
	printf("%s%d\n", "Number of UVs: ", nrOfUV);
	printf("%s%d\n", "Number of Normals: ", nrOfNormals);*/
	file.close();
}
