#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 prjMatrix;


vec3 lightPos = vec3(0, 0, 0);
vec3 lightCol = vec3(255, 255, 255);
float lightStr = 100.0f;

//Light based attributes
out vec3 lPos;
out vec3 lCol;
out float lStr;

//Vertex positioning
out vec3 vertNormal;
out vec3 vertPos;

void main() {
	
	lPos = lightPos;
	lCol = lightCol;
	lStr = lightStr;
	gl_Position = prjMatrix * viewMatrix * worldMatrix * vec4(position, 1.0f);
	vertPos = vec3(worldMatrix * vec4(position, 1.0f));

	vertNormal = normal;
}