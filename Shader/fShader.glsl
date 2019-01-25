#version 440 core

in vec3 color;

out vec4 fragment_color;
vec3 col = vec3(0, 0.5, 0.5);

void main() {

	fragment_color = vec4(color, 1); 
}