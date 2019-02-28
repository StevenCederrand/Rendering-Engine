#version 440 core

layout(location=0) out vec3 gPosition;
layout(location=1) out vec3 gNormal;
layout(location=2) out vec4 gColorSpecular;


uniform sampler2D colorTexture;
uniform sampler2D nMap;

//Not this i think
uniform vec3 ambientCol;
uniform vec3 diffuseCol;	
uniform vec3 specCol;
uniform float transparency;
uniform float specularWeight;

in FRAG_DATA {
	vec2 frag_uv;
	vec3 frag_normals;
	vec3 frag_position;
	flat int frag_type;
} frag_data;

void main() {

	gPosition = frag_data.frag_position;
	gNormal = vec3(1,1,1); //normalize(frag_data.frag_normals);
	gColorSpecular = vec4(texture(colorTexture, frag_data.frag_uv).rgb, 0.1f); //We can set the 'a' value to be the a specular map
	gColorSpecular += vec4(texture(nMap, frag_data.frag_uv).rgb, 0.1f); 
}