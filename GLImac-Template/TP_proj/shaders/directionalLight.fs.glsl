#version 330 core


in vec3 vFragPosition;
in vec3 vFragVCNormal;
in vec2 vFragTexCoords;

out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

uniform sampler2D uTexture;

vec3 blinnPhong()
{
	vec3 halfVector = (normalize(-vFragPosition) + uLightPos_vs)/2.0;
	return (uLightIntensity)*(uKd*(dot(normalize(uLightPos_vs - vFragPosition),vFragVCNormal)) + uKs*pow(dot(halfVector,vFragVCNormal),uShininess));
}

void main(){
	fFragColor = ((vec3(texture(uTexture,vFragTexCoords)))*blinnPhong())*0.0 + vec3(texture(uTexture,vFragTexCoords))*0.5;
};
