#include "Zero/Renderer/Renderer2D.h"

#include "Zero/Math/Math.h"
#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    struct Renderer2DStorage
    {
        VertexArrayRef VertexArray{};
        ShaderRef FlatShader{};
        ShaderRef TextureShader{};
    };

    static Renderer2DStorage* s_Data{};

    void Renderer2D::Initialize()
    {
        s_Data = new Renderer2DStorage{
            .VertexArray = VertexArray::Create(),
            .FlatShader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Flat.glsl"),
            .TextureShader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Texture.glsl"),
        };

        VertexBufferRef quadVertexBuffer{ VertexBuffer::Create(
            {
                -0.5f,
                -0.5f,
                0.0f,
                0.0f, //
                0.5f,
                -0.5f,
                1.0f,
                0.0f, //
                0.5f,
                0.5f,
                1.0f,
                1.0f, //
                -0.5f,
                0.5f,
                0.0f,
                1.0f, //
            }
        ) };

        quadVertexBuffer->SetLayout({ { AttributeType::Vector2, "a_Position" }, { AttributeType::Vector2, "a_UV" } });
        s_Data->VertexArray->AddVertexBuffer(quadVertexBuffer);

        IndexBufferRef quadIndexBuffer{ IndexBuffer::Create({ 0, 1, 2, 2, 3, 0 }) };
        s_Data->VertexArray->SetIndexBuffer(quadIndexBuffer);

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Destroy()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_Data->FlatShader->Bind();
        s_Data->FlatShader->SetMatrix4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMatrix4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {}

    void Renderer2D::DrawQuad(const Vector2& position, const Degrees rotation, const Vector2& scale, const Color& color)
    {
        s_Data->FlatShader->Bind();

        Matrix4 modelMatrix{ CalculcateModelMatrix2D(position, rotation, scale) };
        s_Data->FlatShader->SetMatrix4("u_ModelMatrix", modelMatrix);
        s_Data->FlatShader->SetColor("u_Color", color);

        s_Data->VertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }

    void Renderer2D::DrawQuad(const Vector2& position, const Degrees rotation, const Vector2& scale, const Texture2DRef& texture)
    {
        s_Data->TextureShader->Bind();

        Matrix4 modelMatrix{ CalculcateModelMatrix2D(position, rotation, scale) };
        s_Data->TextureShader->SetMatrix4("u_ModelMatrix", modelMatrix);

        texture->Bind();
        s_Data->VertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }
}
