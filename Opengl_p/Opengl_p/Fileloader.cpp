#include "Fileloader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

Object Fileloader::loadObj(std::string path) {
	if (this->getExtension(path) != ".obj") {
		std::cout << "ERROR::PARSING::FILETYPE::NOT::SUPPORTED" << std::endl;
		return Object();
	}
	else {

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
		std::vector<Vertex> orderedNormals;

		std::vector<UV> uv;
		std::vector<Vertex> normals;
		std::vector<Vertex> vertices;
		std::vector<Triangle> triangles;


		std::vector<Vert> verts;
		/*
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
			else if (line[0] == 'f') {
				Vert tempVert = Vert();
				uint8_t slashes = 0;
				for (int i = 1; i < line.length(); i++) {

				}

			}
		}
		*/
		
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
								orderedNormals.push_back(normals.at(std::stoi(val) - 1));

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
								orderedNormals.push_back(normals.at(std::stoi(val) - 1));
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

}

void Fileloader::loadMap(std::string path, int width, int height, int bpp, int cpp)
{
	float matrix[1024][904];
	//glm::mat3 matrix;
	unsigned char* heightMap = stbi_load(path.c_str(), &width, &height, &bpp, cpp);

	std::vector<float> elevation;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{							//kanske är fel, static_cast kanske?
			//float elevation = float(heightMap[(i*width + j) * 4]);
			float elevation = static_cast<float>(*(heightMap + (i*width + j) * 4));

			elevation /= 128;
			elevation--;
			matrix[i][j] = elevation;
		}
	}
	stbi_image_free(heightMap);

	
}

Material Fileloader::loadMaterial(std::string path) {
	
	std::ifstream iFile(path);
	Material tempMat = Material();
		
	if (!iFile.is_open()) {
		std::cout << "ERROR::OPENING::MTL::FILE::" + path << std::endl;
		return tempMat;
	}
	
	std::string line;
	
	glm::vec3 col;
	float x;

	while (std::getline(iFile, line)) {
		//Grab the first word
		std::string fWord = line.substr(0, line.find(' '));

		//Specular exponent
		if (fWord == "Ns") {
			fWord = line.substr(line.find(' ') + 1, line.length());
			tempMat.specularWeight = std::stof(fWord);
		}
		//Ambient Color
		else if (fWord == "Ka") {	
			tempMat.ambientCol = extractVector(line);
		}
		//diffuse colour
		else if (fWord == "Kd") {
			tempMat.diffuseCol = extractVector(line);
		}
		//Specular colour
		else if (fWord == "Ks") {
			tempMat.specularCol = extractVector(line);
		}
		//transparency
		else if (fWord == "d" || fWord == "Tr") {
			fWord = line.substr(line.find(' ') + 1, line.length());
			tempMat.transparency = std::stof(fWord);
		}
		//illuminaton model
		else if (fWord == "illum") {
			fWord = line.substr(line.find(' ') + 1, line.length());
			tempMat.illuminationModel = std::stoi(fWord);
		}
		//Name of the material
		else if (fWord == "newmtl") {
			fWord = line.substr(line.find(' ') + 1, line.length());
			tempMat.name = fWord;
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

//Split at 'const char 'c'' position
std::string Fileloader::split(std::string val, const char c) {
	return " ";
}

Object Fileloader::readFile(std::string path) {

	Mesh mesh;

	std::string line;
	std::fstream file;
	file.open(path.c_str(), std::ios::in);
		
	Object temp = Object();
	
	//We can't open the file
	if (!file.is_open()) { std::cout << "ERROR::NO::FILE::FOUND" << std::endl; return temp; }

	int vertex = 0;
	int uvs = 0;
	int ns = 0;

	while (std::getline(file, line)) {
		//Find the first space
		int dataStart = line.find(' ');
		std::string l = line.substr(0, dataStart);
		if (l == "v") {
			l = line.substr(++dataStart, line.length());
			temp.v.push_back(interpretVec3(l));
			vertex++;
		}
		else if (l == "vt") {
			l = line.substr(++dataStart, line.length());
			temp.uv.push_back(interpretVec2(l));
			uvs++;
		}
		else if (l == "vn") {
			l = line.substr(++dataStart, line.length());
			temp.n.push_back(interpretVec3(l));
			ns++;
		}
		else if (l == "f") {
			l = line.substr(++dataStart, line.length());
			interpretMesh(l, mesh, temp);
		}
		//load material
		else if (l == "mtllib") {
			std::string mtlname = line.substr(l.length() + 1, line.length());
			temp.setMaterial(this->loadMaterial(OBJECTSPATH + mtlname));
		}
	}
	temp.setMesh(mesh);

	return temp;
}

void Fileloader::interpretMesh(std::string line, Mesh &mesh, Object object) { 

	int slashes = 0;
	int index = 0;
	std::string val;

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ') {
			slashes = 0;
			val = "";
		}
		if (i == line.length() - 1) {
			val += line[i];
			mesh.normal.push_back(object.n.at(std::stoi(val) - 1));
		}
		else if (line[i] == '/') {
			switch (slashes) {
				//When we've got vertices in the face
			case 0:
				mesh.vertex.push_back(object.v.at(std::stoi(val) - 1));
				break;
			case 1:
				mesh.uv.push_back(object.uv.at(std::stoi(val) - 1));
				break;
			}
			val = "";
			slashes++;
		}
		else {
			val += line[i];
		}
	}

}

glm::vec3 Fileloader::interpretVec3(std::string line) {
	glm::vec3 pos = glm::vec3(0, 0, 0);
	int val = 0;
	std::string temp = "";
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ' || i == line.length() - 1) {
			pos[val++] = std::stof(temp);
			temp = "";
		}
		else {
			temp += line[i];
		}
	}
	return pos;
}

glm::vec2 Fileloader::interpretVec2(std::string line) {
	glm::vec2 pos = glm::vec2(0, 0);
	int val = 0;
	std::string temp = "";

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ' || i == line.length() - 1) {
			pos[val] = std::stof(temp);
			val++;
			temp = "";
		}
		else {
			temp += line[i];
		}
	}
	return pos;
}

std::string Fileloader::splitAt(std::string path, int at) {
	std::string word = "";
	for (int i = at; i < path.length(); i++) {
		word += path[i];
	}

	return word;
}

bool Fileloader::validExtension(std::string path) {
	int length = path.length();
	//Because we know that the extension is going to be 4 characters long we can assume this
	std::string extension = splitAt(path, length - 4);
	if (extension == ".obj") {
		return true;
	}
	return false;
}