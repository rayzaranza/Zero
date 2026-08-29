#version 460 core

out vec4 o_Color;

uniform vec4 u_Color;

in vec4 v_Color;

void main()
{
	o_Color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
