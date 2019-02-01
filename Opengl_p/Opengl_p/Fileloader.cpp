#include "Fileloader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Fileloader::Fileloader() {
	//Setup the valid file types
	this->validFiletypes.push_back(".obj");
	this->validFiletypes.push_back(".mtl");
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


//void Fileloader::loadMap(std::string path, int width, int height, int bpp, int cpp)
void Fileloader::loadMap(std::string path, int &width, int &height, std::vector<float> &elevation)

{
	//unsigned char* heightMap = stbi_load(path.c_str(), &width, &height, &bpp, cpp);
	//unsigned char* heightMap = stbi_load(path.c_str(), &width, &height, NULL, 1);
	stbi_uc *heightMap = stbi_load(path.c_str(), &width, &height, NULL, 1);

	for (int i = 0; i < height; i++)
	{							
		for (int j = 0; j < width; j++)
		{
			//float elevation = float(heightMap[(i*width + j) * 4]);
			//float elevations = static_cast<float>(*(heightMap + (i*width + j) * 4));
			float elevations = static_cast<float>(*(heightMap + (i*width + j)));

			elevations /= 128;	
			elevations--;
			elevation.push_back(elevations);
			//matrix[i][j] = elevation;
		}
	}
	stbi_image_free(heightMap);

	
}

Material Fileloader::loadMaterial(std::string path) {
	//Check to see if the path is valid
	Material tempMat = Material();
	
	if (!this->validExtension(path)) { return tempMat; }

	std::ifstream iFile(path);
	if (!iFile.is_open()) {
		std::cout << "ERROR::OPENING::MTL::FILE" + path << std::endl;
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
		
	Object temp = Object();
	//in case of an invalid extension
	if (!this->validExtension(path)) { return temp; }
	
	file.open(path.c_str(), std::ios::in);
	//We can't open the file
	if (!file.is_open()) { std::cout << "ERROR::NO::FILE::FOUND" << std::endl; return temp; }

	int vertex = 0;
	int uvs = 0;
	int ns = 0;

	std::vector<Vertex> tmpVerts;
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
			
			interpretMesh(l, mesh, tmpVerts, temp);
		}
		//load material
		else if (l == "mtllib") {
			std::string mtlname = line.substr(l.length() + 1, line.length());
			temp.setMaterial(this->loadMaterial(OBJECTSPATH + mtlname));
		}
	}
	mesh.verts = tmpVerts;
	temp.setMesh(mesh);

	return temp;
}

void Fileloader::interpretMesh(std::string line, Mesh &mesh, std::vector<Vertex> &verts, Object object) {

	int slashes = 0;
	std::string val;

	Vertex temp;

	for (int i = 0; i < line.length(); i++) {
		//Normals
		if (line[i] == ' ') {
			slashes = 0;
			//add a vertex normal
			temp.normal = object.n.at(std::stoi(val) - 1);
			verts.push_back(temp);

			val = "";
		}
		//Normals
		if (i == line.length() - 1) {
			val += line[i];
			//add a vertex normal
			temp.normal = object.n.at(std::stoi(val) - 1);
			verts.push_back(temp);

		}
		else if (line[i] == '/') {
			switch (slashes) {
			//Position
			case 0:
				//add a vertex position
				temp.position = object.v.at(std::stoi(val) - 1);
				break;
			//UV
			case 1:
				if (val != "") {
					//add a vertex UV
					temp.uv = object.uv.at(std::stoi(val) - 1);
				}
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
	bool retVal = false;

	for (int i = 0; i < this->validFiletypes.size(); i++) {
		if (this->validFiletypes.at(i) == extension) {
			retVal = true;
			break;
		}
	}
	if (!retVal) {
		std::cout << "ERROR::INVALID::EXTENSION" << std::endl;
	}
	return retVal;
}