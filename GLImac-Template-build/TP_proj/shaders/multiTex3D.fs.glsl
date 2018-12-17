#version 330 core


in vec3 vFragPosition;
in vec3 vFragVCNormal;
in vec2 vFragTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

void main(){
	vec3 tex1Col = vec3(texture(uTexture,vFragTexCoords));
	vec3 tex2Col = vec3(texture(uTexture2,vFragTexCoords));
	fFragColor = tex1Col + tex2Col;
};
