#type vertex
#version 460 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_UV;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

out vec2 v_UV;

void main()
{
    v_UV = a_UV;
    gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 0.0f, 1.0f);
}

//====================================================================================

#type fragment
#version 460 core

in vec2 v_UV;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

out vec4 o_Color;

void main()
{
    o_Color = texture(u_Texture, v_UV) * u_Color;
}
