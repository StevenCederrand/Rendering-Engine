#version 440 core
in vec2 frag_uv;
out vec4 FragColor;

//The deferred textures
uniform sampler2D positionBuffer;
uniform sampler2D normalBuffer;
uniform sampler2D colourBuffer;
uniform sampler2D depthMap; // depthmap for shadow mapping
uniform vec3 cameraPos; //used to determine where in the world the camera is
uniform int lightCount; //Used for looping through all of the lights
uniform mat4 lightMatrixes; // VP matrixes for shadow mapping

//Material values
uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;
uniform float transparency;
uniform float specularWeight;


float lightStr = 0.2f;
vec3 lightColour = vec3(1);

const int LIGHTS = 32;

struct Pointlight {
	vec4 position;
	//Attenuation Values are here; x = constant, y = linear, z = quadratic
	vec4 factors;
};

uniform Pointlight pointLights[LIGHTS];



float calculateShadow(vec4 positionLightSpace){
	vec3 shadow = positionLightSpace.xyz / positionLightSpace.w;

	shadow = shadow * 0.5 + 0.5;
	float closestDepth = texture(depthMap, shadow.xy).r;
	float currentDepth = shadow.z;
	//return closestDepth;
	//return currentDepth;

	if(currentDepth > 1.0){
		return 0.0;
	}
	currentDepth -= 0.005;
	return currentDepth > closestDepth ? 1.0 : 0.0;
}


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

	vec4 shadowPos = lightMatrixes * vec4(position,1);
	
	vec3 result = vec3(0);
	result = Diffuse.rgb * lightStr; //Ambience
	vec3 viewDirection = normalize(cameraPos - position);
	for(int i = 0; i < lightCount; i++) {
		result +=20 * (lightCalc(pointLights[i], normal, position, Diffuse, viewDirection) * (1 - calculateShadow(shadowPos)));
	}
	//result *= (1 - calculateShadow(shadowPos));

	FragColor = vec4(result, 1);


	float closestDepth = texture(depthMap, frag_uv).r;
	//FragColor = vec4(closestDepth, closestDepth, closestDepth, 1);
}
