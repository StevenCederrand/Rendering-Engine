#version 440 core

layout(location=0) in vec2 pos;
layout(location=1) in vec2 textCoord;

out vec2 frag_textCoord;

void main() {
	gl_Position = vec4(pos, 0, 1);
	frag_textCoord = textCoord;
}