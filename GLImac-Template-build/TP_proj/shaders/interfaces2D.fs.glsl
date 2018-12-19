#version 330 core

// in vec3 vFragColor;
in vec2 vertexTexture;
out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
	fFragColor = texture(uTexture, vertexTexture).xyz;
}
