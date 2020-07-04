#version 450 core

layout ( location = 0 ) in vec2 vPosition;
layout ( location = 1 ) in vec3 vColor;
layout ( location = 2 ) in vec2 vTexCoord;

out vec3 fColor;
out vec2 fTexCoord;

uniform mat4 transMat;

void
main() 
{
	fTexCoord = vTexCoord;
	fColor = vColor;
	gl_Position = transMat * vec4 ( vPosition, 0.0f, 1.0f );
}