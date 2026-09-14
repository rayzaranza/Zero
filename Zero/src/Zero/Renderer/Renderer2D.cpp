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
        ShaderRef Shader{};
        Texture2DRef DefaultTexture{};
    };

    static Renderer2DStorage* s_Data;

    void Renderer2D::Initialize()
    {
        ZR_PROFILE_FUNCTION();

        s_Data = new Renderer2DStorage{};
        s_Data->VertexArray = VertexArray::Create();

        const Array<F32> QUAD_VERTICES{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f };
        const VertexBufferLayout QUAD_ATTRIBUTES{ { AttributeType::Vector2, "a_Position" }, { AttributeType::Vector2, "a_UV" } };
        VertexBufferRef quadVertexBuffer{ VertexBuffer::Create(QUAD_VERTICES) };
        quadVertexBuffer->SetLayout(QUAD_ATTRIBUTES);
        s_Data->VertexArray->AddVertexBuffer(quadVertexBuffer);

        const Array<U32> QUAD_INDICES{ 0, 1, 2, 2, 3, 0 };
        IndexBufferRef quadIndexBuffer{ IndexBuffer::Create(QUAD_INDICES) };
        s_Data->VertexArray->SetIndexBuffer(quadIndexBuffer);

        s_Data->DefaultTexture = Texture2D::Create(glm::uvec2{ 1 });
        constexpr U32 defaultTextureData{ 0xffffffff };
        s_Data->DefaultTexture->SetData(&defaultTextureData, sizeof(U32));

        s_Data->Shader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Default.glsl");
        s_Data->Shader->Bind();
        s_Data->Shader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Destroy()
    {
        ZR_PROFILE_FUNCTION();

        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        ZR_PROFILE_FUNCTION();

        s_Data->Shader->Bind();
        s_Data->Shader->SetMatrix4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
        ZR_PROFILE_FUNCTION();
    }

    void Renderer2D::DrawQuad(const QuadProperties& quad)
    {
        ZR_PROFILE_FUNCTION();

        s_Data->VertexArray->Bind();

        s_Data->Shader->SetMatrix4("u_ModelMatrix", CalculcateModelMatrix2D(quad.Position, quad.Rotation, quad.Scale));
        s_Data->Shader->SetColor("u_Color", quad.Color);

        if (quad.Texture == nullptr)
            s_Data->DefaultTexture->Bind();
        else
            quad.Texture->Bind();

        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const Radians rotation, const glm::vec2& scale, const glm::vec4& color)
    {
        ZR_PROFILE_FUNCTION();

        s_Data->VertexArray->Bind();

        glm::mat4 modelMatrix{ CalculcateModelMatrix2D(position, rotation, scale) };
        s_Data->Shader->SetMatrix4("u_ModelMatrix", modelMatrix);
        s_Data->Shader->SetColor("u_Color", color);

        s_Data->DefaultTexture->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }

    void Renderer2D::DrawQuad(
        const glm::vec2& position, const Radians rotation, const glm::vec2& scale, const Texture2DRef& texture, const glm::vec4& tint
    )
    {
        ZR_PROFILE_FUNCTION();

        s_Data->VertexArray->Bind();

        glm::mat4 modelMatrix{ CalculcateModelMatrix2D(position, rotation, scale) };
        s_Data->Shader->SetMatrix4("u_ModelMatrix", modelMatrix);
        s_Data->Shader->SetColor("u_Color", tint);

        texture->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }
}
