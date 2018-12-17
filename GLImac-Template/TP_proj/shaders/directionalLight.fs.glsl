#version 330 core


in vec3 vFragPosition;
in vec3 vFragVCNormal;

out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong()
{
	vec3 halfVector = (normalize(-vFragPosition) + uLightDir_vs)/2.0;
	return uLightIntensity*(uKd*(dot(normalize(uLightDir_vs),vFragVCNormal)) + uKs*pow(dot(halfVector,vFragVCNormal),uShininess));
}

void main(){
	fFragColor = blinnPhong();
};