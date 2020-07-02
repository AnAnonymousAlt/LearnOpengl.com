#version 450 core

layout ( location = 0 ) out vec4 fColor;

in vec4 outColor;

uniform vec4 timeColor;
uniform int right;

void
main()
{
	
	if (right == 1 )
	{
		fColor = vec4 ( 1.0, 1.0, 1.0, 1.0 );
		
		fColor = outColor;
	}
	else
	{
		fColor = timeColor;
	}

}