#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;

// out vec3 vFragColor;
uniform float uTime;
uniform mat3 uModelMatrix;

out vec2 vertexTexture;


void main() {
	vertexTexture = aVertexTexture;
	gl_Position = vec4((uModelMatrix*vec3(aVertexPosition,1)).xy, 0, 1);
};
