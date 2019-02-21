#version 440 core

in vec2 frag_textCoord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColor;

struct PointLight{	
	vec3 lPos;
	vec3 color;

	float lConstant;
	float lLinear;
	float lQuadratic;
};

const int MAX_LIGHTS = 32;
uniform PointLight lights[MAX_LIGHTS];

uniform vec3 cameraPos;

vec3 shadeIt() {
	vec3 result = vec3(1);

	return result;
}

void main() {
	

}