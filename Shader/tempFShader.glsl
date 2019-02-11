#version 440 core

uniform vec3 cameraPos;
in vec2 frag_uv;
in vec3 frag_normals;

out vec4 fragment_color;

uniform sampler2D colorTexture;
uniform sampler2D normalMap;

void main() {
	vec3 baseCol = vec3(texture(colorTexture, frag_uv));
	vec3 normalCol = vec3(texture(normalMap, frag_uv));

    fragment_color = vec4(normalCol, 1);
}