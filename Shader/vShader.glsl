#version 440 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;
uniform vec3 cameraPos;

//layout(location=1) in vec3 colorData;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 prjMatrix;

out vec3 normals;
out vec2 uvs;
out vec3 fragPos;
out vec3 camPos;

void main() {
	normals = normal;
	gl_Position = prjMatrix * viewMatrix * worldMatrix * vec4(position, 1.0f);
	fragPos = vec3(worldMatrix * vec4(position, 1));
	camPos = cameraPos;
	uvs = uv;
}