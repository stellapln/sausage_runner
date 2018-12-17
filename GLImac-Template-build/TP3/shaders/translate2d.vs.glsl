#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;

mat3 translate(in float x,in float y)
{
	return mat3(
		vec3(1.0,0.0,x),
		vec3(0.0,1.0,y),
		vec3(0.0,0.0,1.0));
}
mat3 scale(in float x,in float y)
{
	return mat3(
		vec3(x,0.0,0.0),
		vec3(0.0,y,0.0),
		vec3(0.0,0.0,1.0));
}
mat3 rotate(in float a)
{
	a = radians(a);
	return mat3(
		vec3(cos(a),-sin(a),0.0),
		vec3(sin(a),cos(a),0.0),
		vec3(0.0,0.0,1.0));
}

void main() {
	vFragColor = aVertexColor;
	mat3 tr = scale(1.0,1.2) * translate(0.1,0.0) * rotate(2);
	gl_Position = vec4((vec3(aVertexPosition,1)*tr).xy,0,1);
};
