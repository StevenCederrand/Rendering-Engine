#version 440 core

layout(location=0) in vec3 position;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 prjMatrix;

void main() {
	
	gl_Position = prjMatrix * viewMatrix * worldMatrix * vec4(position, 1.0f);
}