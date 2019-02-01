#version 440 core

//Uniforms for basic .obj material
uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;
uniform float transparency;
uniform float specularWeight;


in vec3 normals;
in vec2 uvs;
in vec3 fragPos;
in vec3 camPos;

out vec4 fragment_color;


vec3 lightPos = vec3(0, 0, 10);
float lightStr = 3.0f;
vec3 lightCol = vec3(0.1, 0.1, 0.1);

//Set ambient lighting 
vec3 ambience() {
	vec3 amb = vec3(0, 0, 0);
	float ambStr = 0.1f;
	amb = lightCol * lightStr;
	vec3 result = amb * ambientCol;
	return result;
}
//Set diffuse lighting 
vec3 diffuse() {
	vec3 norm = normalize(normals);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(lightDir, norm), 0);
		
	vec3 result = diff * lightCol * lightStr;
	return result;
}
//Set specular lighting 
vec3 specular() {

	vec3 norm = normalize(normals); //This too
	vec3 lightDir = normalize(lightPos - fragPos); //Clean this

	float specularStr = 5.0f; //This should be set to data read in the .obj file
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float specW = specularWeight;
	//Check to see if the specular color is nothing, if so ->defer to default specular weight
	if (specW == 0) {
		specW = 32;
	}
	float spec = pow(max(dot(viewDir, reflectDir), 0), specW); //32 can also be read from the .obj

	vec3 result = specularStr * spec * lightCol;
	return result;
}

void main() {
	
	vec3 result = (ambience() + diffuse() + specular()) * diffuseCol;
	
	fragment_color = vec4(result, 0.1f);
	fragment_color.a = 0.1f;
}