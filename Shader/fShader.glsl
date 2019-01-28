#version 440 core

uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;

in vec3 vertPos;
in vec3 vertNormal;
in vec3 lPos;
in vec3 lCol;
in float lStr;

out vec4 fragment_color;

void main() {

	vec3 norm = normalize(vertNormal);
	vec3 lightDir = normalize(lPos - vertPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lCol;
	
	vec3 ambience = lStr * lCol;
	vec3 result = (diffuse + ambience) * diffuseCol;
	fragment_color = vec4(result, 1); 
}