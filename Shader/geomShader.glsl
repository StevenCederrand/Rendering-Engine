#version 440 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 prjMatrix;

uniform vec3 cameraPosition;

in GEOM_DATA{
	vec3 position;
	vec3 normals;
	vec2 uv;
	int type;
} geom_data[];


out FRAG_DATA {
	vec2 frag_uv;
	vec3 frag_normals;
	vec3 frag_position;
	flat int frag_type;
} frag_data;

out MATRICES {
	mat4 mat_world;
	mat4 mat_view;
	mat4 mat_prj;
} matrices;

vec3 getNormal() {
	vec4 vertices[3];

	for(int i = 0; i < 3; i++) {
		vertices[i] = prjMatrix * viewMatrix * worldMatrix * vec4(geom_data[i].position, 1);
	} 
	
	vec4 edge1 = vertices[1] - vertices[0];
	vec4 edge2 = vertices[2] - vertices[0];
	
	vec3 normal = normalize(cross(vec3(edge1), vec3(edge2)));

	return normal;
}

void culling() {
	bool emit = true;
	vec4 vertex;
	//Commit to this loop so long as we emit the vertex 
	for(int i = 0; i < 3 && emit; i++) {
		//this vertex is in projection space
		vertex = prjMatrix * viewMatrix * worldMatrix * vec4(geom_data[i].position, 1);
		vec3 camToSurface = normalize(vec3(vertex) - cameraPosition);
		if(dot(camToSurface, getNormal()) <= 0) {
			emit = false;
		}
		else {
			gl_Position = vertex;
			frag_data.frag_uv = geom_data[i].uv;
			frag_data.frag_position = vec3(worldMatrix * vec4(geom_data[i].position, 1));
			frag_data.frag_normals = geom_data[i].normals;
			frag_data.frag_type = geom_data[i].type;

			matrices.mat_world = worldMatrix;
			matrices.mat_view = viewMatrix;
			matrices.mat_prj = prjMatrix;

			EmitVertex();
		}
	}
	if(emit) {
		EndPrimitive();
	}
}
void main() {
	culling();

}