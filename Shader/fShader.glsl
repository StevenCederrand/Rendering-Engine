#version 440 core

//Uniforms for basic .obj material
uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;
uniform float transparency;
uniform float specularWeight;


uniform sampler2D colorTexture;
uniform sampler2D normalMap;


in vec3 normals;
in vec2 uvs;
in vec3 fragPos;
in vec3 camPos;

out vec4 fragment_color;


vec3 rgb_normal = texture(normalMap, uvs).rgb;
vec3 lightPos = vec3(0, 2, 5);
float lightStr = 0.5f;
vec3 lightCol = vec3(1, 1, 1);
/*
vec4 phong(vec3 normal, vec3 diffCol) {
	vec4 result = vec4(0, 0, 0, 1);
	normal = normalize(normal * 2 - 1);

	//Ambient lighting 
	vec3 ambient = lightCol * lightStr * diffCol;
	
	//Diffuse
	vec3 posToLight = normalize(lightPos - fragPos);
	float heavyDiff = max(dot(posToLight, normalize(normals)), 0);
	float surNormAngl = max(dot(posToLight, normal), 0);
	vec3 diffuse = lightStr * diffCol * surNormAngl * heavyDiff;

	//Specular
	vec3 temp = camPos;
	vec3 viewDir = normalize((camPos) - fragPos);
	//viewDir = cross(viewDir, cameraLook);
	vec3 reflection = reflect(-posToLight, normal);
	
	vec3 specular = vec3(0);

	if(surNormAngl > 0) {
		specular = lightStr * specCol * pow(max(dot(reflection, viewDir), 0), specularWeight);	

	}

	result.rgb = ambient + diffuse + specular;
	
	return result;
}


*/
void main() {
	vec3 normalText = texture(normalMap, uvs).rgb;
	vec3 diffText = texture(colorTexture, uvs).rgb;

	fragment_color = vec4(1);//phong(normalize(normalText * 0.5 + 0.5), diffText);

}