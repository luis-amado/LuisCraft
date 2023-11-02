#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec3 transform;

void main() {
	gl_Position = vec4(aPos + transform, 1.0);
}