#type vertex
#version 460 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_UV;
layout (location = 3) in float a_TextureSlot;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

out vec4 v_Color;
out vec2 v_UV;
out float v_TextureSlot;

void main()
{
    v_Color = a_Color;
    v_TextureSlot = a_TextureSlot;
    v_UV = a_UV;
    gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 0.0f, 1.0f);
}

//========================================================================================================

#type fragment
#version 460 core

in vec4 v_Color;
in vec2 v_UV;
in float v_TextureSlot;

uniform sampler2D u_Textures[32];
uniform vec2 u_Tiling;

out vec4 o_Color;

void main()
{
    o_Color = texture(u_Textures[int(v_TextureSlot)], v_UV) * v_Color;    
}
