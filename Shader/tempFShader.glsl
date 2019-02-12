#version 440 core

uniform vec3 cameraPos;

in FRAG_DATA {
	vec2 frag_uv;
	vec3 frag_normals;
	vec3 frag_position;

} frag_data;

out vec4 fragment_color;

uniform sampler2D colorTexture;
uniform sampler2D normalMap;

vec3 lightPos = vec3(0, 10, 0);
float lightStr = 1.0f;
vec3 lightCol = vec3(1, 1, 1);

vec4 phongShading(vec3 diffCol) { 

	//Ambient Shading 
	vec3 ambient = lightCol * lightStr * diffCol;

	//Diffuse Shading
	vec3 posToLight = normalize(lightPos - frag_data.frag_position);

	float diff = max(dot(posToLight, normalize(frag_data.frag_normals)), 0);
	vec3 diffuse = lightStr * diffCol * diff;
	
	return vec4(ambient + diffuse, 1);
}


void main() {
	vec3 normalText = texture(normalMap, frag_data.frag_uv).rgb;
	vec3 diffText = texture(colorTexture, frag_data.frag_uv).rgb;

    fragment_color = phongShading(diffText);
}