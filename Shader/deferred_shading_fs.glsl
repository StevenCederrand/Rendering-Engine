#version 440 core

out vec4 fragment_color;

in vec2 frag_textCoord;


layout(location = 0) uniform sampler2D gPosition;
layout(location = 1) uniform sampler2D gNormal;
layout(location = 2) uniform sampler2D gColorSpecular;

uniform int lightCount;

struct PointLight{	
	vec3 lPos;
	vec3 color;

	float lConstant;
	float lLinear;
	float lQuadratic;
	float radius; //Radius of shine 
};

const int MAX_LIGHTS = 32;
uniform PointLight lights[MAX_LIGHTS];

uniform vec3 cameraPos;

void main() {
	float lightStr = 1.0f;

	vec3 normal = texture(gNormal, frag_textCoord).rgb;
	vec3 fragPos = texture(gPosition, frag_textCoord).rgb;
	vec3 diffCol = texture(gColorSpecular, frag_textCoord).rgb;
	float specularStr = texture(gColorSpecular, frag_textCoord).a;

	for(int i = 0; i < lightCount; i++) {
		float dist = length(lights[i].lPos - fragPos);
		vec3 lightDirection = normalize(lights[i].lPos - fragPos);
		vec3 diffuse = max(dot(normal, lightDirection), 0.0f) * diffCol * lights[i].color;
		//Calculate attenuation
		float attenuation = 1.0/(lights[i].lConstant + (lights[i].lLinear * dist) + lights[i].lQuadratic * pow(dist, 2));

		//ambient += (diffuse * attenuation);
	}
	/*
	vec3 ambient = diffCol * lightStr;
	vec3 viewDirection = normalize(cameraPos - fragPos);
	vec3 lightPos = vec3(0);
	for(int i = 0; i < lightCount; i++) {
		float dist = length(lights[i].lPos - fragPos);

		//if(dist < lights[i].radius) {
			//Diffuse
			vec3 lightDirection = normalize(lights[i].lPos - fragPos);
			vec3 diffuse = max(dot(normal, lightDirection), 0.0f) * diffCol * lights[i].color;
			//Calculate attenuation
			float attenuation = 1.0/(lights[i].lConstant + (lights[i].lLinear * dist) + lights[i].lQuadratic * pow(dist, 2));
			ambient += (diffuse * attenuation);
		//}

	}*/

	fragment_color = vec4(normal, 1);
	if(normal.x == 0 && normal.y == 0 && normal.z == 0) {
		fragment_color = vec4(1, 0, 1, 1);
	}
	else {
		fragment_color = vec4(diffCol, 1);
	}
	//fragment_color = texture(gNormal, frag_textCoord);
}