#version 440 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

out vec2 geom_uv;   
out vec3 geom_normals;

out GEOM_DATA {
	vec3 position;
	vec3 normals;
	vec2 uv;
} geom_data;

void main() {
	geom_data.position = position;
	geom_data.normals = normal;
	geom_data.uv = uv;
}