#version 440 core

layout(location = 0) in vec3 Position;

uniform mat4 lightMatrixes;
uniform mat4 worldMatrix;


void main(){
	//vec3 temp =vec3(worldMatrix * vec4(Position, 1.0));
	gl_Position = lightMatrixes * (worldMatrix * vec4(Position, 1.0));

}