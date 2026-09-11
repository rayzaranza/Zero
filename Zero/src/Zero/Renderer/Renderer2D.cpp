#include "Zero/Renderer/Renderer2D.h"

#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    struct Renderer2DStorage
    {
        VertexArrayRef VertexArray{};
        ShaderRef Shader{};
    };

    static Renderer2DStorage* s_Data{};

    void Renderer2D::Initialize()
    {
        s_Data = new Renderer2DStorage{
            .VertexArray = VertexArray::Create(),
            .Shader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Flat.glsl"),
        };

        VertexBufferRef quadVertexBuffer{ VertexBuffer::Create({ -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f }) };
        quadVertexBuffer->SetLayout({ { AttributeType::Vector2, "a_Position" } });
        s_Data->VertexArray->AddVertexBuffer(quadVertexBuffer);

        IndexBufferRef quadIndexBuffer{ IndexBuffer::Create({ 0, 1, 2, 2, 3, 0 }) };
        s_Data->VertexArray->SetIndexBuffer(quadIndexBuffer);
    }

    void Renderer2D::Destroy()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_Data->Shader->Bind();
        s_Data->Shader->SetMatrix4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
        s_Data->Shader->SetMatrix4("u_ModelMatrix", Zero::Matrix4{ 1.0f });
    }

    void Renderer2D::EndScene()
    {}

    void Renderer2D::DrawQuad(const Vector3& position, const Vector2& size, const Degrees rotation, const Color& color)
    {
        Matrix4 modelMatrix{ 1.0f };
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), Vector3{ 0, 0, 1 });
        modelMatrix = glm::scale(modelMatrix, Vector3{ size, 1.0f });

        s_Data->Shader->Bind();
        s_Data->Shader->SetMatrix4("u_ModelMatrix", modelMatrix);
        s_Data->Shader->SetColor("u_Color", color);

        s_Data->VertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }

    void Renderer2D::DrawQuad(const Vector2& position, const Vector2& size, const Degrees rotation, const Color& color)
    {
        Renderer2D::DrawQuad(Vector3{ position, 0.0f }, size, rotation, color);
    }
}
