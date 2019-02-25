#version 440 core

layout(location=0) out vec3 gPosition;
layout(location=1) out vec3 gNormal;
layout(location=2) out vec4 gColor;


#define LIGHTS 2
uniform vec3 cameraPos;

//Uniforms for basic .obj material

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

out vec4 fragment_color;

uniform sampler2D colorTexture;
uniform sampler2D normalMap;



void main() {

	gPosition = frag_data.frag_position;
	gNormal = normalize(frag_data.frag_normals);
	gColor = vec4(texture(colorTexture, frag_data.frag_uv).rgb, 1); //We can set the 'a' value to be the a specular map

}