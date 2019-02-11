#version 440 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 prjMatrix;

in GEOM_DATA{
	vec3 position;
	vec3 normals;
	vec2 uv;
} geom_data[];

out vec2 frag_uv;
out vec3 frag_normals;

void main() {
    for(int i = 0; i < 3; i++) {
        frag_uv = geom_data[i].uv*40.0f;
		frag_normals = geom_data[i].normals;

		gl_Position = prjMatrix * viewMatrix * worldMatrix * vec4(geom_data[i].position, 1);
        EmitVertex();
    }
    EndPrimitive();
}