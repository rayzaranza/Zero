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
    };

    //======================================================================================
    //  Renderer2D Data
    //======================================================================================
    struct Renderer2DData
    {
        Ref<VertexArray> QuadVertexArray{};
        Ref<VertexBuffer> QuadVertexBuffer{};
        Ref<Shader> QuadShader{};
        Ref<Texture2D> QuadDefaultTexture{};

        const U32 MaxQuads{ 10000 };
        const U32 MaxVertices{ MaxQuads * 4 };
        const U32 MaxIndices{ MaxQuads * 6 };

        U32 QuadIndexCount{ 0 };

        QuadVertex* QuadVertexBufferBase{ nullptr };
        QuadVertex* QuadVertexBufferPtr{ nullptr };
    };

    //======================================================================================
    //  Renderer2D
    //======================================================================================
    static Renderer2DData s_Data;

    void Renderer2D::Initialize()
    {
        ZR_PROFILE_FUNCTION();

        s_Data.QuadVertexArray = VertexArray::Create();

        s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxQuads * sizeof(QuadVertex));
        s_Data.QuadVertexBuffer->SetLayout(
            { { AttributeType::Vector2, "a_Position" }, { AttributeType::Vector4, "a_Color" }, { AttributeType::Vector2, "a_UV" } }
        );

        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

        U32* quadIndices{ new U32[s_Data.MaxIndices] };

        U32 offset{ 0 };
        for (U32 i{ 0 }; i < s_Data.MaxIndices; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        IndexBufferRef quadIndexBuffer{ IndexBuffer::Create(quadIndices, s_Data.MaxIndices) };
        s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
        delete[] quadIndices;

        s_Data.QuadDefaultTexture = Texture2D::Create(glm::uvec2{ 1 });
        constexpr U32 defaultTextureData{ 0xffffffff };
        s_Data.QuadDefaultTexture->SetData(&defaultTextureData, sizeof(defaultTextureData));

        s_Data.QuadShader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Default.glsl");
        s_Data.QuadShader->Bind();
        s_Data.QuadShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Destroy()
    {
        ZR_PROFILE_FUNCTION();
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        ZR_PROFILE_FUNCTION();

        s_Data.QuadShader->Bind();
        s_Data.QuadShader->SetMatrix4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
        s_Data.QuadShader->SetMatrix4("u_ModelMatrix", glm::mat4{ 1.0f });

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    }

    void Renderer2D::EndScene()
    {
        ZR_PROFILE_FUNCTION();

        const U32 dataSize{ static_cast<U32>((U8*)s_Data.QuadVertexBufferPtr - (U8*)s_Data.QuadVertexBufferBase) };
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
    }

    void Renderer2D::DrawQuad(const QuadProperties& quad)
    {
        ZR_PROFILE_FUNCTION();

        s_Data.QuadVertexBufferPtr->Position = quad.Position;
        s_Data.QuadVertexBufferPtr->Color = quad.Color;
        s_Data.QuadVertexBufferPtr->UV = glm::vec2{ 0.0f, 0.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = glm::vec2{ quad.Position.x + quad.Scale.x, quad.Position.y };
        s_Data.QuadVertexBufferPtr->Color = quad.Color;
        s_Data.QuadVertexBufferPtr->UV = glm::vec2{ 1.0f, 0.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = glm::vec2{ quad.Position.x + quad.Scale.x, quad.Position.y + quad.Scale.y };
        s_Data.QuadVertexBufferPtr->Color = quad.Color;
        s_Data.QuadVertexBufferPtr->UV = glm::vec2{ 1.0f, 1.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = glm::vec2{ quad.Position.x, quad.Position.y + quad.Scale.y };
        s_Data.QuadVertexBufferPtr->Color = quad.Color;
        s_Data.QuadVertexBufferPtr->UV = glm::vec2{ 0.0f, 1.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const Radians rotation, const glm::vec2& scale, const glm::vec4& color)
    {
        ZR_PROFILE_FUNCTION();

        s_Data.QuadVertexArray->Bind();

        glm::mat4 modelMatrix{ CalculcateModelMatrix2D(position, rotation, scale) };
        s_Data.QuadShader->SetMatrix4("u_ModelMatrix", modelMatrix);
        s_Data.QuadShader->SetColor("u_Color", color);
        s_Data.QuadShader->SetVector2("u_Tiling", glm::vec2{ 1.0f });

        s_Data.QuadDefaultTexture->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
    }

    void Renderer2D::DrawQuad(
        const glm::vec2& position,
        const Radians rotation,
        const glm::vec2& scale,
        const Texture2DRef& texture,
        const glm::vec4& tint,
        const glm::vec2& tiling
    )
    {
        ZR_PROFILE_FUNCTION();

        s_Data.QuadVertexArray->Bind();

        glm::mat4 modelMatrix{ CalculcateModelMatrix2D(position, rotation, scale) };
        s_Data.QuadShader->SetMatrix4("u_ModelMatrix", modelMatrix);
        s_Data.QuadShader->SetColor("u_Color", tint);
        s_Data.QuadShader->SetVector2("u_Tiling", tiling);

        texture->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
    }
}
