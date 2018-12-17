# version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;

out vec2 vFragTexture;
out vec2 vFragPosition;

uniform mat3 uModelMatrix;


mat3 rotate(in float a)
{
	a = radians(a);
	return mat3(
		vec3(cos(a),-sin(a),0.0),
		vec3(sin(a),cos(a),0.0),
		vec3(0.0,0.0,1.0));
}

void main() {
	vFragTexture = aVertexTexture;
	//vFragPosition = vec2(vec3(aVertexPosition,0.0)*rotate(450.0));
	gl_Position = vec4(vec3(aVertexPosition,1.0)*uModelMatrix,1);
}
