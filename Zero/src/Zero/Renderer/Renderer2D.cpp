#include "Zero/Renderer/Renderer2D.h"

#include "Zero/Math/Math.h"
#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    //======================================================================================
    //  Constants
    //======================================================================================
    static constexpr U32 QUAD_INDEX_COUNT{ 6u };
    static constexpr U32 QUAD_VERTEX_COUNT{ 4u };
    static constexpr U32 MAX_QUADS{ 10000u };
    static constexpr U32 MAX_VERTICES{ MAX_QUADS * QUAD_VERTEX_COUNT };
    static constexpr U32 MAX_INDICES{ MAX_QUADS * QUAD_INDEX_COUNT };
    static constexpr U32 MAX_TEXTURE_SLOTS{ 32u };
    static constexpr U32 DEFAULT_TEXTURE_SLOT_INDEX{ 0u };
    static constexpr glm::vec2 QUAD_VERTEX_POSITIONS[4]{
        { -0.5f, -0.5f },
        { 0.5f, -0.5f },
        { 0.5f, 0.5f },
        { -0.5f, 0.5f },
    };
    static constexpr glm::vec2 QUAD_VERTEX_UVS[4]{
        { 0.0f, 0.0f },
        { 1.0f, 0.0f },
        { 1.0f, 1.0f },
        { 0.0f, 1.0f },
    };

    //======================================================================================
    //  Quad Vertex
    //======================================================================================
    struct QuadVertex
    {
        glm::vec2 Position{ 0.0f };
        glm::vec4 Color{ 1.0f };
        glm::vec2 UV{ 0.0f };
        F32 TextureSlot{ 0.0f };
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

        U32 QuadIndexCount{ 0u };
        QuadVertex* QuadVertexBufferBase{ nullptr };
        QuadVertex* QuadVertexBufferPointer{ nullptr };

        FixedArray<Texture2DRef, MAX_TEXTURE_SLOTS> Textures{};
    };

    static Renderer2DData s_Data{};

    //======================================================================================
    //  Helper Functions
    //======================================================================================
    static void GenerateQuadIndexBuffer();

    //======================================================================================
    //  Renderer2D Initializer
    //======================================================================================
    void Renderer2D::Initialize()
    {
        ZR_PROFILE_FUNCTION();

        s_Data.QuadVertexArray = VertexArray::Create();

        s_Data.QuadVertexBuffer = VertexBuffer::Create(MAX_QUADS * sizeof(QuadVertex));
        s_Data.QuadVertexBuffer->SetLayout(
            { { AttributeType::Vector2, "a_Position" },
              { AttributeType::Vector4, "a_Color" },
              { AttributeType::Vector2, "a_UV" },
              { AttributeType::Float, "a_TextureSlot" },
              { AttributeType::Vector2, "a_Tiling" } }
        );

        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

        s_Data.QuadVertexBufferBase = new QuadVertex[MAX_VERTICES];

        GenerateQuadIndexBuffer();

        I32 textureSamplers[MAX_TEXTURE_SLOTS]{};
        for (U32 i{ 0u }; i < MAX_TEXTURE_SLOTS; ++i)
        {
            textureSamplers[i] = i;
        }

        s_Data.QuadShader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Default.glsl");
        s_Data.QuadShader->Bind();
        s_Data.QuadShader->SetIntArray("u_Textures", textureSamplers, MAX_TEXTURE_SLOTS);

        s_Data.DefaultTexture = Texture2D::Create(glm::uvec2{ 1u });
        constexpr U32 defaultTextureData{ 0xffffffff };
        s_Data.DefaultTexture->SetData(&defaultTextureData, sizeof(defaultTextureData));
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
    }

    static F32 GetTextureSlot(const Renderer2D::QuadProperties& quad)
    {
        if (quad.Texture == nullptr)
        {
            return static_cast<F32>(DEFAULT_TEXTURE_SLOT_INDEX);
        }

        for (U32 i{ 0u }; i < MAX_TEXTURE_SLOTS; i++)
        {
            if (s_Data.Textures[i] == nullptr)
            {
                s_Data.Textures[i] = quad.Texture;
                return static_cast<F32>(i);
            }

            if (s_Data.Textures[i]->GetRendererID() == quad.Texture->GetRendererID())
            {
                return static_cast<F32>(i);
            }
        }

        return static_cast<F32>(DEFAULT_TEXTURE_SLOT_INDEX);
    }

    static glm::vec2 GetTansformedVertexPosition(const U32 index, const glm::mat4& transform)
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

        F32 textureIndex{ GetTextureSlot(quad) };

        const glm::mat4 transform{ CalculcateModelMatrix2D(quad.Position, quad.Rotation, quad.Scale) };

        for (U32 i{ 0u }; i < QUAD_VERTEX_COUNT; ++i)
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
    }

    //======================================================================================
    //  Renderer2D Flush/Submit
    //======================================================================================
    void Renderer2D::Flush()
    {
        ZR_PROFILE_FUNCTION();

        for (U32 i{ 0u }; i < s_Data.Textures.size(); ++i)
        {
            if (!s_Data.Textures[i])
            {
                break;
            }

            s_Data.Textures[i]->Bind(i);
        }

        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
    }

    void Renderer2D::EndScene()
    {
        ZR_PROFILE_FUNCTION();

        const U32 dataSize{ static_cast<U32>((U8*)s_Data.QuadVertexBufferPointer - (U8*)s_Data.QuadVertexBufferBase) };
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Destroy()
    {
        ZR_PROFILE_FUNCTION();
    }

    //======================================================================================
    //  Helper Functions Definitions
    //======================================================================================
    void GenerateQuadIndexBuffer()
    {
        U32* quadIndices{ new U32[MAX_INDICES] };

        U32 offset{ 0u };
        for (U32 index{ 0u }; index < MAX_INDICES; index += QUAD_INDEX_COUNT)
        {
            quadIndices[index + 0u] = offset + 0u;
            quadIndices[index + 1u] = offset + 1u;
            quadIndices[index + 2u] = offset + 2u;
            quadIndices[index + 3u] = offset + 2u;
            quadIndices[index + 4u] = offset + 3u;
            quadIndices[index + 5u] = offset + 0u;
            offset += QUAD_VERTEX_COUNT;
        }

        IndexBufferRef quadIndexBuffer{ IndexBuffer::Create(quadIndices, MAX_INDICES) };
        s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
        delete[] quadIndices;
    }
}
