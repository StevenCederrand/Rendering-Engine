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


Object Fileloader::loadMap(std::string path)
{
	// here we load the map
	int width;
	int height;
	std::vector<float> elevation;
	stbi_uc *heightMap = stbi_load(path.c_str(), &width, &height, NULL, 1);
	//width /= 20;
	//height /= 20;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			//go along the width, height times so that we get all the elevations from the picture
			float elevations = float(heightMap[(j*width + i)]);
	
			elevations /= 32.0f;
			elevation.push_back(elevations);

		}
	}

	stbi_image_free(heightMap);

	struct TriangleVertex { float x, y, z; };
	int size = width * height;
	int counter = 0;
	int index = 0;
	//create a trianglevertex vector
	//TriangleVertex *triangleVertices = new TriangleVertex[size];
	TriangleVertex triangleVertices2;
	std::vector<TriangleVertex> TVerts;

	Object objMap = Object();
	Mesh meshMap = Mesh();
	std::vector<Vertex> mapPosition;
	Vertex vert;

	glm::vec3 normal1, normal2;
	glm::vec2 uV;
	int position1, position2, position3, position4;
	float height2 = 1.0f / height;
	float width2 = 1.0f / width;
	for (size_t j = 0; j < (height-1); j++)
	{
		for (size_t i = 0; i < (width-1); i++)
		{
			position1 = (width * j) + i;				//upper left			
			triangleVertices2.x = (float)i;
			triangleVertices2.y = elevation[position1] * 0.1f;//divide by a number so that it looks more "flat"
			triangleVertices2.z = (float)j;
			TVerts.push_back(triangleVertices2);

			position2 = (width * j) + (i + 1);			//upper right
			triangleVertices2.x = (float)i + 1;
			triangleVertices2.y = elevation[position2] * 0.1f;;//divide by a number so that it looks more "flat"
			triangleVertices2.z = (float)j;
			TVerts.push_back(triangleVertices2);

			position3 = (width *(j + 1)) + i;			//bottom left
			triangleVertices2.x = (float)i;
			triangleVertices2.y = elevation[position3] * 0.1f;;//divide by a number so that it looks more "flat"
			triangleVertices2.z = (float)j + 1;
			TVerts.push_back(triangleVertices2);

			position4 = (width *(j + 1)) + (i + 1);		//bottom right
			triangleVertices2.x = (float)i + 1;
			triangleVertices2.y = elevation[position4] * 0.1f;;//divide by a number so that it looks more "flat"
			triangleVertices2.z = (float)j + 1;
			TVerts.push_back(triangleVertices2);

			glm::vec3 firstV = glm::vec3(TVerts.at(counter).x, TVerts.at(counter).y, TVerts.at(counter).z); counter++;
			glm::vec3 secondV = glm::vec3(TVerts.at(counter).x, TVerts.at(counter).y, TVerts.at(counter).z); counter++;

			glm::vec3 thirdV = glm::vec3(TVerts.at(counter).x, TVerts.at(counter).y, TVerts.at(counter).z); counter++;
			glm::vec3 fourthV = glm::vec3(TVerts.at(counter).x, TVerts.at(counter).y, TVerts.at(counter).z); counter++;

			normal1 = -(glm::normalize(glm::cross(firstV - secondV, firstV - thirdV)));
			normal2 = -(glm::normalize(glm::cross(fourthV - thirdV, fourthV - secondV)));
			//glm::vec2 uV = glm::vec2(0.333333, 0.666667);
			//first vertex to first triangle first line 1-2
			vert.position = (firstV);
			vert.normal = (normal1);
			uV = glm::vec2(firstV.x*width2, firstV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(firstV);
			objMap.n.push_back(normal1);
			objMap.uv.push_back(uV);

			//second vertex to first triangle first line 1-2
			vert.position = (secondV);
			vert.normal = (normal1);
			uV = glm::vec2(secondV.x*width2, secondV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(secondV);
			objMap.n.push_back(normal1);
			objMap.uv.push_back(uV);
			/*
			//second vertex to first triangle second line 2-3
			vert.position = (secondV);
			vert.normal = (normal1);
			uV = glm::vec2(secondV.x*width2, secondV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(secondV);
			objMap.n.push_back(normal1);
			objMap.uv.push_back(uV);

			//third vertex to first triangle second line 2-3
			vert.position = (thirdV);
			vert.normal = (normal1);
			uV = glm::vec2(thirdV.x*width2, thirdV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(thirdV);

			//first vertex to first triangle third line 1-3
			vert.position = (firstV);
			vert.normal = (normal1);
			uV = glm::vec2(firstV.x*width2, firstV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(firstV);
			objMap.n.push_back(normal1);
			objMap.uv.push_back(uV);

			*/
			//third vertex to first triangle third line 1-3	
			vert.position = (thirdV);
			vert.normal = (normal1);
			uV = glm::vec2(thirdV.x*width2, thirdV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(thirdV);
			objMap.n.push_back(normal1);
			objMap.uv.push_back(uV);


			//first vertex to second triangle first line 2-3
			vert.position = (secondV);
			vert.normal = (normal2);
			uV = glm::vec2(secondV.x*width2, secondV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(secondV);
			objMap.n.push_back(normal2);
			objMap.uv.push_back(uV);

			//second vertex to second triangle first line 2-3
			vert.position = (thirdV);
			vert.normal = (normal2);
			uV = glm::vec2(thirdV.x*width2, thirdV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(thirdV);
			objMap.n.push_back(normal2);
			objMap.uv.push_back(uV);

			/*

			//second vertex to second triangle second line 3-4
			vert.position = (thirdV);
			vert.normal = (normal2);
			uV = glm::vec2(thirdV.x*width2, thirdV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(thirdV);
			objMap.n.push_back(normal2);
			objMap.uv.push_back(uV);


			//third vertex to second triangle second line 3-4
			vert.position = (fourthV);
			vert.normal = (normal2);
			uV = glm::vec2(fourthV.x*width2, fourthV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(fourthV);
			objMap.n.push_back(normal2);
			objMap.uv.push_back(uV);


			//first vertex to second triangle third line 2-4
			vert.position = (secondV);
			vert.normal = (normal2);
			uV = glm::vec2(secondV.x*width2, secondV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(secondV);
			objMap.n.push_back(normal2);
			objMap.uv.push_back(uV);
			*/

			//third vertex to second triangle third line 2-4
			vert.position = (fourthV);
			vert.normal = (normal2);
			uV = glm::vec2(fourthV.x*width2, fourthV.z*height2);
			vert.uv = (uV);
			mapPosition.push_back(vert);

			objMap.v.push_back(fourthV);
			objMap.n.push_back(normal2);
			objMap.uv.push_back(uV);

		}
	}
			
	meshMap.verts = mapPosition;
	objMap.setMesh(meshMap);
	objMap.setMaterial(loadMaterial(OBJECTSPATH + "ExampleObj.mtl"));
		
	return objMap;
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
		//Handle textures
		else if (line.substr(0, 3) == "map") {
			tempMat.textures.push_back(this->interpretTexture(line));
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

Texture Fileloader::interpretTexture(std::string line) {
	Texture texture;
	int space = line.find(' ');
	std::string textureType = line.substr(0, line.find(' '));
	
	//When dealing with a bump-mapping texture
	if (textureType == "map_Bump") {
		texture.type = Texturetypes::Normal;
		std::string text = line.substr(++space, line.find(' '));
		
		//std::cout << text << std::endl;
		text = "";
		for (int i = line.length() - 1; i > 0; i--) {
			if (line[i] == ' ') {
				break;
			}
			text += line[i];
		}

		//Get the file-name
		std::string name = "";
		for (int i = 0; i < text.length(); i++) {
			name.push_back(text.at(text.length() - i - 1));
		}
		texture.name = name;
	}

	//Diffuse texture
	else if (textureType == "map_Kd") {
		std::string textureName = line.substr(++space, line.length());
		texture.name = textureName;
		texture.type = Texturetypes::Diffuse;
	}

	return texture;
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