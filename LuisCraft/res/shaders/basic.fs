#version 330 core

out vec4 FragColor;

uniform float light;

void main() {
	FragColor = vec4(0.8, 0.2, 0.1, 1.0) * light;
}