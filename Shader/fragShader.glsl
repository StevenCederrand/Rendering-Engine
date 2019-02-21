#version 440 core

layout(location=0) out vec3 gPosition;
layout(location=1) out vec3 gNormal;
layout(location=2) out vec4 gColor;


#define LIGHTS 2
uniform vec3 cameraPos;

//Uniforms for basic .obj material
uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;
uniform float transparency;
uniform float specularWeight;

struct PointLight{	
	vec3 lPos;
	float lConstant;
	float lLinear;
	float lQuadratic;
};

uniform PointLight pointLights[LIGHTS];

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

out vec4 fragment_color;

uniform sampler2D colorTexture;
uniform sampler2D normalMap;

float lightStr = 1.0f;
vec3 lightCol = vec3(1, 1, 1);

vec3 phongShading(PointLight pl, vec3 diffCol) { 
	vec3 normal = mat3(transpose(inverse(matrices.mat_world))) * frag_data.frag_normals;

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
}


vec4 temp(PointLight pl) {

	vec3 normal = mat3(transpose(inverse(matrices.mat_world))) * frag_data.frag_normals;

	vec3 lightDir = normalize(pl.lPos - frag_data.frag_position);

	vec3 viewDirection = normalize(cameraPos - frag_data.frag_position);
	vec3 reflectDir = reflect(-lightDir, normalize(normal));
	float specW = specularWeight ;
	if(specW <= 0) {
		specW = 32;
	}
	float specStr = 0.9f;
	float spec = pow(max(dot(viewDirection, reflectDir), 0), specW);


	vec3 specular =	specStr * lightCol * spec;
	return vec4(1);
}



void main() {
	if(frag_data.frag_type != 2) { 
		vec3 normalText = texture(normalMap, frag_data.frag_uv).rgb;
		vec3 diffText = texture(colorTexture, frag_data.frag_uv).rgb;

		vec3 result = vec3(0);
		result += phongShading(pointLights[0], diffText);
		result += phongShading(pointLights[1], diffText);
		
		fragment_color = vec4(result, 1);
	}
	else {
		fragment_color = vec4(1);
	}


	//vec4(frag_data.frag_position, 1);

	gPosition = frag_data.frag_position;
	gNormal = normalize(frag_data.frag_normals);
	gColor = vec4(texture(colorTexture, frag_data.frag_uv).rgb, 1);

}




/*
	//Light attenuation
	
	
	
	//Ambient Shading 
	vec3 ambient = lightCol * lightStr * diffCol;

	//Diffuse Shading
	vec3 posToLight = normalize(lightPos - frag_data.frag_position);

	float diff = max(dot(posToLight, normalize(normal)), 0);
	vec3 diffuse = lightStr * diffCol * diff;

	//Speculare Shading 
	
	vec3 reflection = reflect(-posToLight, normalize(normal));
	float specW = specularWeight ;
	if(specW <= 0) {
		specW = 32;
	}
	float specStr = 0.5f;
	float spec = pow(max(dot(viewDirection, reflection), 0), specW);
	vec3 specular = specStr * lightCol * spec;
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

*/