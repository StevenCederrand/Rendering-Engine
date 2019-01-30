#version 440 core

uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;

out vec4 fragment_color;


float ambientStr = 1.0f;
vec3 lightCol = vec3(0.1, 0.1, 0.1);

void main() {

	vec3 ambient = ambientStr * lightCol;
	vec3 result = ambient * ambientCol;

	fragment_color = vec4(diffuseCol, 1); 
}