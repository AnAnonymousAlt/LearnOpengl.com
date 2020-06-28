#version 450 core

uniform vec4 color;
uniform float c;

layout ( location = 0 ) out vec4 fColor;

void
main()
{
	fColor = color;
}