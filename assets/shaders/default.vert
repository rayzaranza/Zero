#version 460 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_UV;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 v_Color;

void main()
{
	vec4 position = vec4(a_Position, 0.0f, 1.0f);
	gl_Position = u_Projection * u_View * position;
	v_Color = vec4(a_UV, 0.0f, 1.0f);
}
