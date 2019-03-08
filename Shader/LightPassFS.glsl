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

	//Attenuation Values are here
	vec4 factors;

};

float linear = 0.7f;
float quadratic = 1.8f;

uniform Pointlight pointLights[LIGHTS];
void main() {
	//Set the output colour to be that of the texture coming in. 
	vec3 position = texture(positionBuffer, frag_uv).rgb;
	vec3 normal = texture(normalBuffer, frag_uv).rgb;
	vec4 Diffuse = texture(colourBuffer, frag_uv);
	
	vec3 result = Diffuse.rgb * 0.4f;

	vec3 cameraDirection = normalize(cameraPos - position);
	for(int i = 0; i < lightCount; i++) {
        // diffuse
        vec3 lightDir = normalize(pointLights[i].position.xyz - position);
        vec3 diffuse = max(dot(normal, lightDir), 0.0) * Diffuse.rgb * lightColour;
        // specular
		float specularStr = 0.5f;
		vec3 reflectionDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(cameraDirection, reflectionDir), 0.0), 32);
		vec3 Specular = specularStr * spec * lightColour;
        // attenuation
        float dist = length(pointLights[i].position.xyz - position);
        float attenuation = 1.0 / (pointLights[i].factors.x + (pointLights[i].factors.y * dist) + (pointLights[i].factors.z * dist * dist));
        diffuse *= attenuation;


//        specular *= attenuation;
        result += diffuse + Specular;
	}
	
	FragColor = vec4(result, 1);
}