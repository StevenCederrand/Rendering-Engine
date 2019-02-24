#version 440 core

in vec2 frag_textCoord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColor;
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

out vec4 fragment_color;

/*
vec3 phongShading(PointLight pl) { 




	vec3 lightDir = normalize(pl.lPos - frag_data.frag_position);
	//Used for diffuse shading
	float angle = max(dot(frag_data.frag_normals, lightDir), 0.0);
	//Used for specular shading
	vec3 viewDirection = normalize(cameraPos - frag_data.frag_position);
	vec3 reflectDir = reflect(-lightDir, normalize(normal));
	float specW = specularWeight ;
	if(specW <= 0) {
		specW = 32;
	}
	float specStr = 0.5f;
	float spec = pow(max(dot(viewDirection, reflectDir), 0), specW);

	float lDistance = length(pl.lPos - frag_data.frag_position);
	float attenuation = 1.0/(pl.lConstant + (pl.lLinear * lDistance) + pl.lQuadratic * pow(lDistance, 2));
	
	vec3 ambient = lightCol * lightStr * diffCol;
	vec3 diffuse = diffCol * angle * lightStr;
	vec3 specular =	specStr * lightCol * spec;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return vec3(ambient + diffuse + specular);
}*/


void main() {
	float lightStr = 1.0f;

	vec3 normal = texture(gNormal, frag_textCoord).rgb;
	vec3 fragPos = texture(gPosition, frag_textCoord).rgb;
	vec3 diffCol = texture(gColor, frag_textCoord).rgb;
	float specularStr = texture(gColor, frag_textCoord).a;

	vec3 ambient = diffCol * lightStr;
	vec3 viewDirection = normalize(cameraPos - fragPos);

	for(int i = 0; i < lightCount; i++) {
		float dist = length(lights[i].lPos - fragPos);

		if(dist < lights[i].radius) {
			//Diffuse
			vec3 lightDirection = normalize(lights[i].lPos - fragPos);
			vec3 diffuse = max(dot(normal, lightDirection), 0.0f) * diffCol * lights[i].color;
			//Calculate attenuation
			float attenuation = 1.0/(lights[i].lConstant + (lights[i].lLinear * dist) + lights[i].lQuadratic * pow(dist, 2));
		}
	}

}