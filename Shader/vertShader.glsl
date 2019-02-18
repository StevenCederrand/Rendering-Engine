#version 440 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform int type;


out vec2 geom_uv;   
out vec3 geom_normals;

out GEOM_DATA {
	vec3 position;
	vec3 normals;
	vec2 uv;
	int type;
} geom_data;


//Also includes lightSources
void standard() {
	geom_data.position = position;
	geom_data.normals = normal;
	geom_data.uv = uv;
}

void heighMapBased() {
	geom_data.position = position;
	geom_data.normals = normal;
	geom_data.uv = uv * 40;
}

void main() {
	//Standard / lightsource
	if(type == 0 || type == 2) {
		standard();
	}
	else if(type == 1) {
		heighMapBased();
	}
	geom_data.type = type;
}

