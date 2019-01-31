#version 440 core

uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;

in vec3 normals;
in vec2 uvs;
in vec3 fragPos;
in vec3 camPos;

out vec4 fragment_color;


vec3 lightPos = vec3(0, 0, 10);

float lightStr = 100.0f;
vec3 lightCol = vec3(0.1, 0.1, 0.1);

vec3 ambience() {
	
	vec3 amb = vec3(0, 0, 0);
	float ambStr = 0.1f;
	amb = lightCol * ambStr;
	vec3 result = amb * ambientCol;
	return result;
}


vec3 diffuse() {
	vec3 norm = normalize(normals);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(lightDir, norm), 0);
		
	vec3 result = diff * lightCol;
	return result;
}

vec3 specular() {

	vec3 norm = normalize(normals); //This too
	vec3 lightDir = normalize(lightPos - fragPos); //Clean this

	float specularStr = 1.0f; //This should be set to data read in the .obj file
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0), 124); //32 can also be read from the .obj

	vec3 result = specularStr * spec * lightCol;
	return result;
}
void main() {
	
	vec3 result = (ambience() + diffuse() + specular()) * diffuseCol;

	fragment_color = vec4(result, 1); 
}