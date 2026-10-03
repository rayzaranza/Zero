#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_UV;
layout(location = 3) in int a_TextureSlot;
layout(location = 4) in vec2 a_Tiling;
layout(location = 5) in int a_EntityID;

uniform mat4 u_ViewProjectionMatrix;

out vec4 v_Color;
out vec2 v_UV;
out flat int v_TextureSlot;
out vec2 v_Tiling;
out flat int v_EntityID;

void main()
{
    v_Color = a_Color;
    v_TextureSlot = a_TextureSlot;
    v_Tiling = a_Tiling;
    v_UV = a_UV;
    v_EntityID = a_EntityID;
    gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0f);
}


//========================================================================================================


#type fragment
#version 460 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_Color2;

in vec4 v_Color;
in vec2 v_UV;
in flat int v_TextureSlot;
in vec2 v_Tiling;
in flat int v_EntityID;

uniform sampler2D u_Textures[32];

void main()
{
    o_Color = texture(u_Textures[v_TextureSlot], v_UV * v_Tiling) * v_Color;
    o_Color2 = v_EntityID;
}
