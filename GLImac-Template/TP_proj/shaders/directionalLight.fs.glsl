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

#define DIRECTIONNAL 0
#define POINT 1

#define MAX_N_LIGHT 50

struct Light
{
	vec3 pos;
	vec3 intensity;
	int type;
};


uniform int numberOfSecondaryLights;
uniform Light secondaryLights[MAX_N_LIGHT];

vec3 blinnPhongDir(Light light)
{
	vec3 halfVector = (normalize(-vFragPosition) + light.pos)/2.0;
	return (light.intensity)*(uKd*(dot(normalize(light.pos - vFragPosition),vFragVCNormal)) + uKs*pow(dot(halfVector,vFragVCNormal),uShininess));
}
vec3 blinnPhongPoint(Light light)
{
	vec3 halfVector = (normalize(-vFragPosition) + light.pos)/2.0;
	float d = distance(light.pos,vFragPosition);
	return (light.intensity/(d*d))*(uKd*(dot(normalize(light.pos - vFragPosition),vFragVCNormal)) + uKs*pow(dot(halfVector,vFragVCNormal),uShininess));
}

vec3 blinnPhong(Light light)
{
	if(light.type == DIRECTIONNAL) return blinnPhongDir(light);
	return blinnPhongPoint(light);
}

void main(){
	vec3 texture = vec3(texture(uTexture,vFragTexCoords));

	Light globalLight;
	globalLight.pos = uLightPos_vs;
	globalLight.intensity = uLightIntensity;
	globalLight.type = POINT;

	vec3 blPh = blinnPhong(globalLight);

	for(int i = 0;i < numberOfSecondaryLights && i < MAX_N_LIGHT;i++)
	{
		blPh += blinnPhong(secondaryLights[i]);
	}
	blPh.x = clamp(blPh.x,0.0,1.0);
	blPh.y = clamp(blPh.y,0.0,1.0);
	blPh.z = clamp(blPh.z,0.0,1.0);
	fFragColor = texture*0.3 + texture*blPh*0.7;
};
