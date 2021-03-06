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
	float d = distance(uLightPos_vs,vFragPosition);
	return (uLightIntensity/(d*d))*(uKd*(dot(normalize(uLightPos_vs - vFragPosition),vFragVCNormal)) + uKs*pow(dot(halfVector,vFragVCNormal),uShininess));
}

void main(){
	fFragColor = (vec3(texture(uTexture,vFragTexCoords))+vec3(0.1,0.1,0.1))*blinnPhong();
};
