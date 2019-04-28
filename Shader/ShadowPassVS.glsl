#version 440 core

layout(location = 0) in vec3 Position;

uniform mat4 lightMatrixes;
uniform mat4 worldMatrix;


void main(){
	gl_Position = lightMatrixes * (worldMatrix * vec4(Position, 1.0));

}