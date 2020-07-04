#version 450 core

out vec4 outColor;
in vec2 fTexCoord;

uniform sampler2D sContainer;

void
main ()
{
	outColor = texture ( sContainer, fTexCoord );
}