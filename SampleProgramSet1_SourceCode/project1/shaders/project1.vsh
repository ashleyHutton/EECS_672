#version 410 core

// replace the placeholder implementation here
in vec2 mcPosition;
uniform vec4 scaleTrans;

void main()
{
	float ldsx = (scaleTrans[0] * mcPosition.x) + scaleTrans[1];
	float ldsy = (scaleTrans[2] * mcPosition.y) + scaleTrans[3];
	gl_Position = vec4(ldsx, ldsy, 0, 1);
}

