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
#define MAX_SHADOW_CALC 50
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

vec3 vClamp(vec3 v,float a, float b)
{
	v.x = clamp(v.x,a,b);
	v.y = clamp(v.y,a,b);
	v.z = clamp(v.z,a,b);
	return v;
}

void main(){
	vec3 texture = vec3(texture(uTexture,vFragTexCoords));
	vec3 blPh = vec3(0.0);

	Light globalLight;
	globalLight.pos = uLightPos_vs;
	globalLight.intensity = uLightIntensity;
	globalLight.type = DIRECTIONNAL;
	blPh = blinnPhong(globalLight);

	vec3 currentLight;

	for(int i = 0;i < numberOfSecondaryLights && i < MAX_N_LIGHT;i++)
	{
		//blPh += blinnPhong(secondaryLights[i]);
		currentLight = blinnPhong(secondaryLights[i]);
		blPh += vClamp(currentLight,0.0,1.0);
	}

	blPh = vClamp(blPh,0.0,1.0);

	if(distance(vec3(0.0),vFragPosition) > MAX_SHADOW_CALC)
	{
		fFragColor = texture;
	}
	else
	{
		fFragColor = texture*0.2 + texture*blPh*0.8;
	}
};