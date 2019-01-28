#version 440 core

uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;


out vec4 fragment_color;

void main() {

	fragment_color = vec4(diffuseCol, 1); 
}