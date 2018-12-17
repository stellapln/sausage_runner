#version 330 core

in vec3 vFragColor;

out vec3 fFragColor;

void main(){
	float gray = (vFragColor.x + vFragColor.y + vFragColor.z)/3;
	fFragColor.x = gray;
	fFragColor.y = gray;
	fFragColor.z = gray;
};
