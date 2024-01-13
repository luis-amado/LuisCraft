#version 330 core

out vec4 fragColor;

in vec2 pos;

uniform vec4 color;
uniform vec4 parent; // x, y, w, h

void main() {
	if(gl_FragCoord.x < parent.x || gl_FragCoord.y < parent.y || gl_FragCoord.x > parent.x + parent.z || gl_FragCoord.y > parent.y + parent.w) {
		//discard;
	}

	fragColor = color;

}