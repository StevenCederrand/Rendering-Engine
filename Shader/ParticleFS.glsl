#version 440 core

in vec4 frag_colour;

out vec4 finalColour;
void main(){

	if(frag_colour.a < 0.1)
		discard;
	
	finalColour = frag_colour;


}