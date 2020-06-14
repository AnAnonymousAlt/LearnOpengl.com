#version 450 core
layout ( location = 0 ) in vec4 vPosition;
void
main () 
{
	vec4 multiplier = vec4 (0.1f, 0.1f, 1.0f, 1.0f);
	vec4 vPosition_ = vPosition * multiplier;
	vPosition_ = vPosition_ - 0.3;
	gl_Position = vPosition;
} 