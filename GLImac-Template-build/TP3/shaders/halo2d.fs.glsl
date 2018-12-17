#version 330 core

in vec2 vFragPostion;
in vec3 vFragColor;

out vec3 fFragColor;

void main(){
	float d = distance(vec2(0.0,0.0),vFragPostion);
	float a = 5.0 * exp(-10.0 * d*d); // HALO

	// a = length(fract(5.0*vFragPostion));
	fFragColor = vFragColor*a;
};
