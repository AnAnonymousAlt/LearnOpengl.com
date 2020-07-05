#version 450 core

out vec4 outColor;
in vec2 fTexCoord;

uniform sampler2D sContainer;
uniform sampler2D sFace;

void
main ()
{
	outColor = mix ( texture ( sContainer, fTexCoord ),
					 texture ( sFace, fTexCoord ),
					 0.2 );
}