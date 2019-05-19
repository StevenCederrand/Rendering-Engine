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
	mat3 TBN;
	flat int frag_type;
} frag_data;

uniform sampler2D colorTexture;
uniform sampler2D normalMap;

void main() {


	vec3 normals = texture(normalMap, frag_data.frag_uv).rgb;//normalize(2*texture(normalMap, frag_data.frag_uv).rgb) - 1;
	normals = normalize(normals * 2 - 1);
	normals = normalize(vec3(frag_data.TBN * normals));

	colourBuffer = texture(colorTexture, frag_data.frag_uv)*3;
	normalBuffer = normals; //normals;
	//normalBuffer = normalize(frag_data.frag_normals);
	positionBuffer = frag_data.frag_position;
}