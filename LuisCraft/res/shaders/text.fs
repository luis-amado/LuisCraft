#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform vec4 textColor;
uniform sampler2D fontAtlas;

void main() {

	float alpha = texture(fontAtlas, texCoord).a;

	fragColor = vec4(1.0, 1.0, 1.0, alpha) * textColor;
}