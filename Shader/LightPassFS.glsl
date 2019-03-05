#version 440 core
in vec2 frag_uv;
out vec4 FragColor;

//The deferred textures
uniform sampler2D positionBuffer;
uniform sampler2D normalBuffer;
uniform sampler2D colourBuffer;
uniform vec3 cameraPos; //used to determine where in the world the camera is
uniform int lightCount; //Used for looping through all of the lights

//Material values
uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;
uniform float transparency;
uniform float specularWeight;


float lightStr = 0.5f;
vec3 lightColour = vec3(1);

const int LIGHTS = 32;

struct Pointlight {
	vec3 position;

	//Values used for attenuating the light
	float constant;
	float linear;
	float quadratic;
};

uniform Pointlight pointLights[LIGHTS];

vec3 phong(vec3 position, vec3 normal, vec4 colour) {
	vec3 result = vec3(0);
	vec3 ambient = colour.rgb * lightStr;
	vec3 viewDirection = normalize(cameraPos - position);

	vec3 diffuse = vec3(0);
	
	
	for(int i = 0; i < lightCount; i++) {
		vec3 lightDirection = normalize(pointLights[i].position - position);
		float angle = max(dot(lightDirection, normal), 0.0);
		diffuse += colour.rgb * angle * lightStr;
		float dist = length(pointLights[i].position - position);
		float attenuation = 1/(pointLights[i].constant + (pointLights[i].linear * dist) + (pointLights[i].quadratic * dist * dist));
		diffuse *= attenuation;
	}
	result = ambient + diffuse;
	return result;
}

void main() {
	//Set the output colour to be that of the texture coming in. 
	vec3 posCol = texture(positionBuffer, frag_uv).rgb;
	vec3 normCol = normalize(texture(normalBuffer, frag_uv).rgb);
	vec4 colour = texture(colourBuffer, frag_uv);

	vec3 result = phong(posCol, normCol, colour);

	FragColor = vec4(result, 1);
}