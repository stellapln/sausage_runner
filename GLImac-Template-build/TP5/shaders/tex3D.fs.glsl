#version 330 core


in vec3 vFragPosition;
in vec3 vFragVCNormal;
in vec2 vFragTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main(){
	fFragColor = vec3(texture(uTexture,vFragTexCoords));
};
