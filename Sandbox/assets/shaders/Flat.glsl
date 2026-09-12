#type vertex
#version 460 core

layout (location = 0) in vec2 a_Position;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
    vec4 position = vec4(a_Position, 0.0f, 1.0f);
    gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * position;
}

//====================================================================================

#type fragment
#version 460 core

out vec4 o_Color;

uniform vec4 u_Color;

void main()
{
    o_Color = u_Color;
}
