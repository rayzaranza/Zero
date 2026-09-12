#include "Zero/Renderer/Renderer2D.h"

#include "Zero/Math/Math.h"
#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    static const Array<F32> QUAD_VERTICES{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f };
    static const Array<U32> QUAD_INDICES{ 0, 1, 2, 2, 3, 0 };
    static const VertexBufferLayout QUAD_ATTRIBUTES{ { AttributeType::Vector2, "a_Position" }, { AttributeType::Vector2, "a_UV" } };

    struct Renderer2DStorage
    {
        VertexArrayRef VertexArray{};
        ShaderRef Shader{};
        Texture2DRef DefaultTexture{};
    };

    static Renderer2DStorage* s_Data{};

    void Renderer2D::Initialize()
    {
        s_Data = new Renderer2DStorage{
            .VertexArray = VertexArray::Create(),
            .Shader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Default.glsl"),
            .DefaultTexture = Texture2D::Create(Vector2u{ 1 }),
        };

        VertexBufferRef quadVertexBuffer{ VertexBuffer::Create(QUAD_VERTICES) };
        IndexBufferRef quadIndexBuffer{ IndexBuffer::Create(QUAD_INDICES) };

        quadVertexBuffer->SetLayout(QUAD_ATTRIBUTES);

        s_Data->VertexArray->AddVertexBuffer(quadVertexBuffer);
        s_Data->VertexArray->SetIndexBuffer(quadIndexBuffer);

        constexpr U32 defaultTextureData{ 0xffffffff };
        s_Data->DefaultTexture->SetData(&defaultTextureData, sizeof(U32));

        s_Data->Shader->Bind();
        s_Data->Shader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Destroy()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_Data->Shader->Bind();
        s_Data->Shader->SetMatrix4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {}

    void Renderer2D::DrawQuad(const Vector2& position, const Degrees rotation, const Vector2& scale, const Color& color)
    {
        s_Data->VertexArray->Bind();

        Matrix4 modelMatrix{ CalculcateModelMatrix2D(position, rotation, scale) };
        s_Data->Shader->SetMatrix4("u_ModelMatrix", modelMatrix);
        s_Data->Shader->SetColor("u_Color", color);

        s_Data->DefaultTexture->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }

    void Renderer2D::DrawQuad(
        const Vector2& position, const Degrees rotation, const Vector2& scale, const Texture2DRef& texture, const Color& tint
    )
    {
        s_Data->VertexArray->Bind();

        Matrix4 modelMatrix{ CalculcateModelMatrix2D(position, rotation, scale) };
        s_Data->Shader->SetMatrix4("u_ModelMatrix", modelMatrix);
        s_Data->Shader->SetColor("u_Color", tint);

        texture->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }
}
