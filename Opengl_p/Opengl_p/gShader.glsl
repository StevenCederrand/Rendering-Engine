#version 440 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

//Matrixes for the world
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 prjMatrix;

in vec2 uv[];
out vec2 uvs;
out vec3 normals;


vec3 norm;
void calculateNormal() {
	vec4 vertices[3];
	for(int i = 0; i < 3; i++) {
		vertices[i] = prjMatrix * viewMatrix * modelMatrix * gl_in[i].gl_Position;
	}

	vec4 edge1 = vertices[1] - vertices[0];
	vec4 edge2 = vertices[2] - vertices[0];
	
	vec3 edgeA = vec3(edge1);
	vec3 edgeB = vec3(edge2);
	
	norm = cross(edgeA, edgeB);
}

void main() {

}