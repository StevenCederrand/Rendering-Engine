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


float lightStr = 1.f;
vec3 lightColour = vec3(1);

const int LIGHTS = 32;

struct Pointlight {
	vec4 position;
	//Attenuation Values are here; x = constant, y = linear, z = quadratic
	vec4 factors;
};

uniform Pointlight pointLights[LIGHTS];

vec3 lightCalc(Pointlight pl, vec3 normal, vec3 position, vec4 colour, vec3 viewDir) {
	//diffuse
	vec3 lightDirection = normalize(pl.position.xyz - position);
	vec3 diffuse = max(dot(normal, lightDirection), 0.0) * colour.rgb;

	//specular
	vec3 reflectionDir = reflect(-lightDirection, normal);
	float spec = pow(max(dot(reflectionDir, viewDir), 0.0), 32);
	vec3 specular = lightColour * spec * 0.5f;
	//Attenuation
	float dist = length(pl.position.xyz - position);
	float attenuation = 1.0 / (pl.factors.x + pl.factors.y * dist + pl.factors.z * (dist * dist)); 
	diffuse *= attenuation;
	specular *= attenuation;

	return vec3(diffuse + specular);
}

void main() {
	//Set the output colour to be that of the texture coming in. 
	vec3 position = texture(positionBuffer, frag_uv).rgb;
	vec3 normal = normalize(texture(normalBuffer, frag_uv).rgb);
	vec4 Diffuse = texture(colourBuffer, frag_uv);
	
	vec3 result = vec3(0);
	result = Diffuse.rgb * 0.1f; //Ambience
	vec3 viewDirection = normalize(cameraPos - position);
	for(int i = 0; i < lightCount; i++) {
		result += lightCalc(pointLights[i], normal, position, Diffuse, viewDirection);
	}

	FragColor = vec4(result, 1);
}
