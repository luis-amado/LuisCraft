#version 330 core

layout (location = 0) in vec2 a_Pos;

uniform mat4 projection;
uniform mat4 model;

vec2 pos;

void main() {

	gl_Position = projection * model * vec4(a_Pos, 0.0, 1.0);
}