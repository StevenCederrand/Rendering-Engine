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
vec3 lightPos = vec3(10, 10, 10);
float lightStr = 0.5f;
vec3 lightCol = vec3(1, 1, 1);

//Set ambient lighting 
vec3 ambience() {
	vec3 amb = vec3(0, 0, 0);
	amb = lightCol * lightStr;
	vec3 result = amb * ambientCol;//texture(colorTexture, uvs).rgb;
	return result;
}

/*

	vec3 nO = rgb_normal;
	nO = normalize(nO);


	vec3 norm = normalize(normals);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(lightDir, nO), 0);
		
	vec3 result = diff * lightCol * lightStr;
	return result * diffuseCol;
*/
//Set diffuse lighting 
vec3 diffuse() {
	vec3 result = vec3(0, 0, 0);
	vec3 norm = normalize(normals);
	
	//AB = (B - A);
	vec3 lightDir = normalize(lightPos - fragPos);
	float heavyDiff = max(dot(norm, lightDir), 0);
	
	norm = (rgb_normal);
	float lightDiff = max(dot(norm, lightDir), 0);
	
	result = ((lightDiff + heavyDiff) * lightCol * lightStr);

	return result * texture(colorTexture, uvs).rgb;
}

//Set specular lighting 

/*
	vec3 nO = rgb_normal;
	nO = normalize(nO * 2.0 - 1.0);


	vec3 norm = normalize(nO); //This too
	vec3 lightDir = normalize(lightPos - fragPos); //Clean this

	float specularStr = 1.0f; //This should be set to data read in the .obj file
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, nO);
	float specW = specularWeight;
	//Check to see if the specular color is nothing, if so ->defer to default specular weight
	if (specW == 0) {
		specW = 32;
	}
	float spec = pow(max(dot(viewDir, reflectDir), 0), specW); //32 can also be read from the .obj

	vec3 result = specularStr * spec * lightCol;

	//Second try
		/*
	vec3 result = vec3(0, 0, 0);
	
	vec3 norm = normalize(normals);
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 viewDir = normalize(camPos - fragPos);
	float specStr = 0.5f;
	
	vec3 reflectDir = reflect(-lightDir, norm);
	float specW = specularWeight;
	//Check to see if the specular color is nothing, if so ->defer to default specular weight
	if (specW == 0) {
		specW = 32;
	}

	float heavySpec = pow(max(dot(viewDir, reflectDir), 0), specW);

	norm = normalize((rgb_normal));

	reflectDir = reflect(-lightDir, norm);

	float lightSpec = pow(max(dot(viewDir, reflectDir), 0), specW);

	result = specStr * lightSpec * lightCol;*/


vec3 specular() {
	

	vec3 nO = rgb_normal;
	nO = normalize(nO * 2.0 - 1.0);


	vec3 norm = normalize(nO); //This too
	vec3 lightDir = normalize(lightPos - fragPos); //Clean this

	float specularStr = 0.25f; //This should be set to data read in the .obj file
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, nO);
	float specW = specularWeight;
	//Check to see if the specular color is nothing, if so ->defer to default specular weight
	if (specW == 0) {
		specW = 32;
	}
	float spec = pow(max(dot(viewDir, reflectDir), 0), specW); //32 can also be read from the .obj

	vec3 result = specularStr * spec * lightCol;
	return result;
}
vec3 temp() {
	vec3 result;

	vec3 norm = normalize(rgb_normal);
	vec3 heavyNorm = normalize(normals);
	vec3 lightToPos = normalize(fragPos - lightPos);
	vec3 posToCam = normalize(camPos - fragPos);
	vec3 reflection = reflect(lightToPos, heavyNorm);
	
	float specStr = 1.0f;
	float specW = specularWeight;
	//Check to see if the specular color is nothing, if so ->defer to default specular weight
	if (specW == 0) {
		specW = 32;
	}
	float spec = pow(max(dot(posToCam, reflection), 0.0), specW); //32 can also be read from the .obj
	
	if(spec > 0) {
		vec3 reflection = reflect(lightToPos, norm);
		spec += pow(max(dot(posToCam, reflection), 0.0), specW);
	}

	result = spec * specStr * lightCol;


	return result;
}

void main() {
	
	//vec3 result = (ambience() + diffuse() + specular());// * texture(colorTexture, uvs).rgb;//diffuse() + texture(colorTexture, uvs).rgb;;//(ambience() + diffuse()) * texture(colorTexture, uvs).rgb; //(ambience() + diffuse() + specular()) * vec3(texture(colorTexture, uvs));
	//vec4 res = texture(normalMap, uvs);
	//fragment_color = vec4(result, texture(colorTexture, uvs).a);
	fragment_color = vec4(1, 1, 1, 1);
}