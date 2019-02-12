#version 440 core

//Uniforms for basic .obj material
uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;
uniform float transparency;
uniform float specularWeight;


uniform sampler2D colorTexture;
uniform sampler2D normalMap;

in FRAG_DATA {
	vec2 frag_uv;
	vec3 frag_normals;
	vec3 frag_position;

} frag_data;

out vec4 fragment_color;


vec3 rgb_normal = texture(normalMap, frag_data.frag_uv).rgb;
vec3 lightPos = vec3(0, 2, 5);
float lightStr = 0.5f;
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

	fragment_color = phongShading(diffText);//phong(normalize(normalText * 0.5 + 0.5), diffText);
}



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