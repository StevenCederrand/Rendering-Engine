	#version 440 core

uniform vec3 cameraPos;

//Uniforms for basic .obj material
uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specCol;
uniform float transparency;
uniform float specularWeight;



in MATRICES {
	mat4 mat_world;
	mat4 mat_view;
	mat4 mat_prj;
} matrices;

in FRAG_DATA {
	vec2 frag_uv;
	vec3 frag_normals;
	vec3 frag_position;

} frag_data;

out vec4 fragment_color;

uniform sampler2D colorTexture;
uniform sampler2D normalMap;

vec3 lightPos = vec3(0, 10, 0);
float lightStr = 1.0f;
vec3 lightCol = vec3(1, 1, 1);

vec4 phongShading(vec3 diffCol) { 

	vec3 normal = mat3(transpose(inverse(matrices.mat_world))) * frag_data.frag_normals;
	
	//Ambient Shading 
	vec3 ambient = lightCol * lightStr * diffCol;

	//Diffuse Shading
	vec3 posToLight = normalize(lightPos - frag_data.frag_position);

	float diff = max(dot(posToLight, normalize(normal)), 0);
	vec3 diffuse = lightStr * diffCol * diff;
	

	//Speculare Shading 
	vec3 viewDirection = normalize(cameraPos - frag_data.frag_position);
	vec3 reflection = reflect(-posToLight, normalize(normal));
	float specW = specularWeight ;
	if(specW <= 0) {
		specW = 32;
	}
	float specStr = 0.5f;
	float spec = pow(max(dot(viewDirection, reflection), 0), specW);
	vec3 specular = specStr * lightCol * spec;
	
	return vec4(ambient + diffuse + specular, 1);
}


void main() {
	vec3 normalText = texture(normalMap, frag_data.frag_uv).rgb;
	vec3 diffText = texture(colorTexture, frag_data.frag_uv).rgb;

    fragment_color = phongShading(diffText);
}