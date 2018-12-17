#version 330 core


in vec3 vFragPosition;
in vec3 vFragVCNormal;
in vec2 vFragTexCoords;

out vec3 fFragColor;

void main(){
	fFragColor = normalize(vFragVCNormal);
};
