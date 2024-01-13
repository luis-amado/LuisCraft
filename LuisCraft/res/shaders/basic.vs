#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aSkyLight;
layout (location = 3) in float aBlockLight;

out vec2 texCoord;
out vec4 light;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D lightMap;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	texCoord = aTexCoord;
	light = texture(lightMap, vec2(aBlockLight, aSkyLight));
}