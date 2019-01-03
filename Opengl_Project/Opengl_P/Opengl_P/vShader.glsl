#version 440 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 colorData;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 prjMatrix;

out vec3 color;


void main() {
	
	color = colorData;
	gl_Position =  prjMatrix * viewMatrix * worldMatrix * vec4(position, 1.0f);
}