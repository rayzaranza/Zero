#include "Zero/Renderer/Renderer2D.h"

#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> VertexArray{};
        Ref<Shader> Shader{};
    };

    static Renderer2DStorage* s_Data{};

    void Renderer2D::Initialize()
    {
        s_Data = new Renderer2DStorage{
            .VertexArray = VertexArray::Create(),
            .Shader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Flat.glsl"),
        };

        Ref<VertexBuffer> quadVertexBuffer{ VertexBuffer::Create({ -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f }) };
        quadVertexBuffer->SetLayout({ { AttributeType::Float2, "a_Position" } });
        s_Data->VertexArray->AddVertexBuffer(quadVertexBuffer);

        Ref<IndexBuffer> quadIndexBuffer{ IndexBuffer::Create({ 0, 1, 2, 2, 3, 0 }) };
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
    }

    void Renderer2D::EndScene()
    {}

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        glm::mat4 modelMatrix{ 1.0f };
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3{ size, 1.0f });

        s_Data->Shader->Bind();
        s_Data->Shader->SetMatrix4("u_ModelMatrix", modelMatrix);
        s_Data->Shader->SetFloat4("u_Color", color);

        s_Data->VertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        Renderer2D::DrawQuad(glm::vec3{ position, 0.0f }, size, color);
    }
}
