#include "Zero/Renderer/Renderer2D.h"

#include "Zero/Math/Math.h"
#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    //======================================================================================
    //  Quad Vertex
    //======================================================================================
    struct QuadVertex
    {
        glm::vec2 Position{ 0.0f };
        glm::vec4 Color{ 1.0f };
        glm::vec2 UV{ 0.0f };
        float TextureSlot{ 0.0f };
        glm::vec2 Tiling{ 1.0f };
    };

    //======================================================================================
    //  Renderer2D Data
    //======================================================================================
    struct Renderer2DData
    {
        VertexArrayRef QuadVertexArray{};
        VertexBufferRef QuadVertexBuffer{};
        ShaderRef QuadShader{};
        Texture2DRef DefaultTexture{};

        uint32_t QuadIndexCount{ 0u };
        QuadVertex* QuadVertexBufferBase{ nullptr };
        QuadVertex* QuadVertexBufferPointer{ nullptr };

        FixedArray<Texture2DRef, MAX_TEXTURE_SLOTS> Textures{};
        uint32_t TextureSlotIndex{ 1u };

        RenderStats Stats{};
    };

    static Renderer2DData s_Data{};

    //======================================================================================
    //  Renderer2D Initializer
    //======================================================================================
    void Renderer2D::Initialize()
    {
        ZR_PROFILE_FUNCTION();

        s_Data.QuadVertexArray = VertexArray::Create();
        s_Data.QuadVertexBuffer = VertexBuffer::Create(MAX_VERTICES * sizeof(QuadVertex));

        s_Data.QuadVertexBuffer->SetLayout(
            { { AttributeType::Vector2, "a_Position" },
              { AttributeType::Vector4, "a_Color" },
              { AttributeType::Vector2, "a_UV" },
              { AttributeType::Float, "a_TextureSlot" },
              { AttributeType::Vector2, "a_Tiling" } }
        );

        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
        s_Data.QuadVertexBufferBase = new QuadVertex[MAX_VERTICES];

        uint32_t* quadIndices{ new uint32_t[MAX_INDICES] };
        uint32_t offset{ 0u };
        for (uint32_t i{ 0u }; i < MAX_INDICES; i += QUAD_INDEX_COUNT)
        {
            quadIndices[i + 0u] = offset + 0u;
            quadIndices[i + 1u] = offset + 1u;
            quadIndices[i + 2u] = offset + 2u;

            quadIndices[i + 3u] = offset + 2u;
            quadIndices[i + 4u] = offset + 3u;
            quadIndices[i + 5u] = offset + 0u;

            offset += QUAD_VERTEX_COUNT;
        }

        Ref<IndexBuffer> quadIndexBuffer{ IndexBuffer::Create(quadIndices, MAX_INDICES) };
        s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
        delete[] quadIndices;

        s_Data.DefaultTexture = Texture2D::Create(glm::uvec2{ 1u });
        constexpr uint32_t defaultTextureData{ 0xffffffff };
        s_Data.DefaultTexture->SetData(&defaultTextureData, sizeof(uint32_t));

        int32_t textureSamplers[MAX_TEXTURE_SLOTS]{};
        for (uint32_t i{ 0u }; i < MAX_TEXTURE_SLOTS; ++i)
        {
            textureSamplers[i] = i;
        }

        s_Data.QuadShader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Default.glsl");
        s_Data.QuadShader->Bind();
        s_Data.QuadShader->SetIntArray("u_Textures", textureSamplers, MAX_TEXTURE_SLOTS);

        s_Data.Textures[DEFAULT_TEXTURE_SLOT_INDEX] = s_Data.DefaultTexture;
    }

    //======================================================================================
    //  Renderer2D Begin Scene
    //======================================================================================
    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        ZR_PROFILE_FUNCTION();

        s_Data.QuadShader->Bind();
        s_Data.QuadShader->SetMatrix4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
        s_Data.QuadShader->SetMatrix4("u_ModelMatrix", { 1.0f });

        s_Data.QuadIndexCount = 0u;
        s_Data.QuadVertexBufferPointer = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1u;
    }

    static glm::vec2 GetTansformedVertexPosition(const uint32_t index, const glm::mat4& transform)
    {
        const glm::vec4 position{ QUAD_VERTEX_POSITIONS[index], 0.0f, 1.0f };
        const glm::vec4 result{ transform * position };

        return { result.x, result.y };
    }

    //======================================================================================
    //  Renderer2D draw quad with struct
    //======================================================================================
    void Renderer2D::DrawQuad(const QuadProperties& quad)
    {
        ZR_PROFILE_FUNCTION();

        if (s_Data.QuadIndexCount >= MAX_INDICES)
        {
            FlushAndReset();
        }

        float textureIndex{ 0.0f };

        if (quad.Texture)
        {
            for (uint32_t i{ 1u }; i < s_Data.TextureSlotIndex; i++)
            {
                if (s_Data.Textures[i]->GetRendererID() == quad.Texture->GetRendererID())
                {
                    textureIndex = static_cast<float>(i);
                    break;
                }
            }

            if (textureIndex == 0.0f)
            {
                textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
                s_Data.Textures[s_Data.TextureSlotIndex] = quad.Texture;
                s_Data.TextureSlotIndex++;
            }
        }

        const glm::mat4 transform{ CalculcateModelMatrix2D(quad.Position, quad.Rotation, quad.Scale) };

        for (uint32_t i{ 0u }; i < 4u; ++i)
        {
            *s_Data.QuadVertexBufferPointer = QuadVertex{
                .Position{ GetTansformedVertexPosition(i, transform) },
                .Color{ quad.Color },
                .UV{ QUAD_VERTEX_UVS[i] },
                .TextureSlot{ textureIndex },
                .Tiling{ quad.Tiling },
            };

            s_Data.QuadVertexBufferPointer++;
        }

        s_Data.QuadIndexCount += QUAD_INDEX_COUNT;
        s_Data.Stats.QuadCount++;
    }

    //======================================================================================
    //  Renderer2D Flush/Submit
    //======================================================================================
    void Renderer2D::Flush()
    {
        ZR_PROFILE_FUNCTION();

        for (uint32_t i{ 0u }; i < s_Data.TextureSlotIndex; i++)
        {
            s_Data.Textures[i]->Bind(i);
        }

        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
        s_Data.Stats.DrawCalls++;
    }

    void Renderer2D::EndScene()
    {
        ZR_PROFILE_FUNCTION();

        uint32_t dataSize{ static_cast<uint32_t>((uint8_t*)s_Data.QuadVertexBufferPointer - (uint8_t*)s_Data.QuadVertexBufferBase) };
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Destroy()
    {
        ZR_PROFILE_FUNCTION();
    }

    void Renderer2D::FlushAndReset()
    {
        EndScene();

        s_Data.QuadIndexCount = 0u;
        s_Data.QuadVertexBufferPointer = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1u;
    }

    //======================================================================================
    //  Stats
    //======================================================================================
    void Renderer2D::ResetStats()
    {
        memset(&s_Data.Stats, 0u, sizeof(RenderStats));
    }

    const RenderStats& Renderer2D::GetStats()
    {
        return s_Data.Stats;
    }
}
