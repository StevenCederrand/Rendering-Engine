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
	std::string correct;
	for (int i = 0; i < extension.length(); i++) {
		correct.push_back(extension.at(extension.length() - i - 1));
	}
	return correct;
}
/*
//OBJ path, Vertices, UV's, Normals, Triangles, Ordered Vertices, Material
void Fileloader::loadObj(std::string path, std::vector<Vertex>& vertices, std::vector<UV>& uv, 
	std::vector<Vertex>& normals, std::vector<Triangle>& triangles, std::vector<Vertex> &orderedVerts, Material* materal) {

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
							orderedVerts.push_back(vertices.at(std::stoi(val) - 1));
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
			triangles.push_back(tempTriangle);
		}
		nrOfLines++;		
	}
	file.close();
}*/

Object Fileloader::loadObj(std::string path) {
	
	Object tempObject = Object();
	
	std::fstream file;
	file.open(path.c_str(), std::ios::in);

	if (!file.is_open()) {
		printf("%s%s\n", "Couldn't open the file at path: ", path);
		return tempObject;
	}
	else {
		printf("%s\n", "File found and opened");
	}
	std::string line;
	std::string mtlName;
	
	std::vector<Vertex> orderedVerts;
	std::vector<UV> uv;
	std::vector<Vertex> normals;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	while (std::getline(file, line)) {
		
		if (line[0] == 'v') {
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
			}
		}
		//Get the material name --- We are assuming that the .mtl file is in the same folder as the .obj
		else if (line[0] == 'm') {
			bool recName = false;
			std::cout << line << std::endl;
			for (int i = 0; i < line.length(); i++) {
				if (recName) {
					mtlName += line[i];
				}
				//When reaching the middle part of the text
				if (line[i] == ' ') {
					recName = true;
				}
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
							tempTriangle.vertices.push_back(vertices.at(std::stoi(val) - 1));
							orderedVerts.push_back(vertices.at(std::stoi(val) - 1));
							break;
						case 1:
							tempTriangle.uvs.push_back(uv.at(std::stoi(val) - 1));
							break;
						case 2:
							tempTriangle.normals.push_back(normals.at(std::stoi(val) - 1));
							break;
						}

					}
					if (line[i] == '/') {
						slashes++;
						val = "";
					}

					if (line[i] == ' ' || i == line.length() - 1) {
						val += line[i];
						//Ghetto fix for adding the last vn
						if (val != " ") {
							tempTriangle.normals.push_back(normals.at(std::stoi(val) - 1));
						}

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
	}
	file.close();
	
	tempObject.setNormals(normals);
	tempObject.setOrderedVertices(orderedVerts);
	tempObject.setTriangles(triangles);
	tempObject.setUV(uv);
	tempObject.setVertices(vertices);
	//Set the material
	tempObject.setMaterial(this->loadMaterial(OBJECTSPATH + mtlName));
	return tempObject;
}

Material* Fileloader::loadMaterial(std::string path) {
	
	std::ifstream iFile(path);
		
	if (!iFile.is_open()) {
		std::cout << "ERROR::OPENING::MTL::FILE::" + path << std::endl;
		return nullptr;
	}
	
	Material* tempMat = new Material();
	std::string line;
	
	glm::vec3 col;
	float x;

	while (std::getline(iFile, line)) {
		//Grab the first word
		std::string fWord = line.substr(0, line.find(' '));

		//Specular exponent
		if (fWord == "Ns") {
			fWord = line.substr(line.find(' ') + 1, line.length());
			tempMat->specularWeight = std::stof(fWord);
		}
		//Ambient Color
		else if (fWord == "Ka") {	
			tempMat->ambientCol = extractVector(line);
			/*std::cout << "Ambient Color: " + std::to_string(tempMat->ambientCol.x) + " " +
				std::to_string(tempMat->ambientCol.y) + " " + std::to_string(tempMat->ambientCol.z) << std::endl;*/
		}
		//diffuse colour
		else if (fWord == "Kd") {
			tempMat->diffuseCol = extractVector(line);
			/*std::cout << "Diffuse Color: " + std::to_string(tempMat->diffuseCol.x) + " " +
				std::to_string(tempMat->diffuseCol.y) + " " + std::to_string(tempMat->diffuseCol.z) << std::endl;*/
		}
		//Specular colour
		else if (fWord == "Ks") {
			tempMat->specularCol = extractVector(line);
			/*std::cout << "specular Color: " + std::to_string(tempMat->specularCol.x) + " " +
				std::to_string(tempMat->specularCol.y) + " " + std::to_string(tempMat->specularCol.z) << std::endl;*/
		}
		//transparency
		else if (fWord == "d" || fWord == "Tr") {
			fWord = line.substr(line.find(' ') + 1, line.length());
			tempMat->transparency = std::stof(fWord);

			/*std::cout << "Transparency: ";
			std::cout << tempMat->transparency << std::endl;*/
		}
		//illuminaton model
		else if (fWord == "illum") {
			fWord = line.substr(line.find(' ') + 1, line.length());
			tempMat->illuminationModel = std::stoi(fWord);
			/*std::cout << "illum: ";
			std::cout << tempMat->illuminationModel << std::endl;*/
		}
		//Name of the material
		else if (fWord == "newmtl") {
			fWord = line.substr(line.find(' ') + 1, line.length());
			tempMat->name = fWord;

			/*std::cout << "matname: ";
			std::cout << tempMat->name << std::endl;*/
		}

	}
	iFile.close();
	return tempMat;
}

glm::vec3 Fileloader::extractVector(std::string line) {
	glm::vec3 col;
	uint8_t traversal = 0;
	std::string fWord = "";

	for (int i = line.find(' ') + 1; i < line.length(); i++) {

		//If we haven't stumbled upon a gap
		if (line[i] != ' ') {
			fWord += line[i];
		}
		if (i == line.length() - 1) {
			col[traversal] = std::stof(fWord);
			fWord = "";
			traversal++;
		}
		else if (line[i] == ' ') {
			//std::cout << fWord << std::endl;
			col[traversal] = std::stof(fWord);
			fWord = "";
			traversal++;
		}
	}
	return col;

}