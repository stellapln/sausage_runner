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

vec3 blinnPhongDir()
{
	vec3 halfVector = (normalize(-vFragPosition) + uLightPos_vs)/2.0;
	return (uLightIntensity)*(uKd*(dot(normalize(uLightPos_vs - vFragPosition),vFragVCNormal)) + uKs*pow(dot(halfVector,vFragVCNormal),uShininess));
}
vec3 blinnPhongPoint()
{
	vec3 halfVector = (normalize(-vFragPosition) + uLightPos_vs)/2.0;
	float d = distance(uLightPos_vs,vFragPosition);
	return (uLightIntensity/(d*d))*(uKd*(dot(normalize(uLightPos_vs - vFragPosition),vFragVCNormal)) + uKs*pow(dot(halfVector,vFragVCNormal),uShininess));
}

void main(){
	vec3 texture = vec3(texture(uTexture,vFragTexCoords));
	vec3 blPh = blinnPhongDir();
	blPh.x = clamp(blPh.x,0.0,1.0);
	blPh.y = clamp(blPh.y,0.0,1.0);
	blPh.z = clamp(blPh.z,0.0,1.0);
	fFragColor = texture*0.5 + texture*blPh*0.5;
};
