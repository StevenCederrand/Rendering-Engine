#version 440 core

layout(location=0) out vec3 positionBuffer;
layout(location=1) out vec3 normalBuffer;
layout(location=2) out vec4 colourBuffer;

in MATRICES {
	mat4 mat_world;
	mat4 mat_view;
	mat4 mat_prj;
} matrices;

in FRAG_DATA {
	vec2 frag_uv;
	vec3 frag_normals;
	vec3 frag_position;
	flat int frag_type;
} frag_data;

uniform sampler2D colorTexture;
uniform sampler2D normalMap;

void main() {
	vec3 normals = (2*texture(normalMap, frag_data.frag_uv).rgb) - 1;

	colourBuffer = texture(colorTexture, frag_data.frag_uv);
	normalBuffer = normalize(frag_data.frag_normals);
	positionBuffer = frag_data.frag_position;
}