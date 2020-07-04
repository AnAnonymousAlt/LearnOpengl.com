#version 450 core

layout ( location = 0 ) out vec4 outColor;

in vec3 fColor;
in vec2 fTexCoord;

uniform vec4 crimson;
uniform sampler2D sContainer;
uniform sampler2D sFace;

void
main()
{
	
	outColor = mix ( texture ( sContainer, fTexCoord ) * vec4 ( fColor, 1.0f ), 
					 texture ( sFace, fTexCoord ), 
					 0.2);
	// outColor = vec4 ( fColor, 1.0f );
}
