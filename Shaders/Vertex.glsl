#version 450 core

layout ( location = 0 ) in vec4 vPosition;
layout ( location = 1 ) in vec4 vColor;
out vec4 outColor;
uniform int right;

void
main() 
{
	if ( right == 1 )
	{
		vec2 move = vec2 ( vPosition );
		move.x = move.x + 0.55;
		gl_Position = vec4 ( move, 0.0f, 1.0f );
		outColor = vColor;
	}
	else 
	{
		vec2 move = vec2 ( vPosition );
		move.x = move.x - 0.55;
		move.y = -move.y;
		gl_Position = vec4 ( move, 0.0f, 1.0f );

	}

}