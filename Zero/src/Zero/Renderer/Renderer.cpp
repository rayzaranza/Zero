#include "Zero/Renderer/Renderer.h"

#include "Zero/Renderer/Renderer2D.h"

namespace Zero
{
    Scope<Renderer::SceneData> Renderer::s_SceneData{ CreateScope<Renderer::SceneData>() };

    void Renderer::Initialize()
    {
        ZR_PROFILE_FUNCTION();

        RenderCommand::Initialize();
        Renderer2D::Initialize();
    }

    void Renderer::Destroy()
    {
        Renderer2D::Destroy();
    }

    void Renderer::OnWindowResized(const glm::uvec2& size)
    {
        RenderCommand::SetViewport({ 0, 0 }, size);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::Submit(const VertexArrayRef& vertexArray, const ShaderRef& shader, const glm::mat4& modelMatrix)
    {
        shader->Bind();
        shader->SetMatrix4("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
        shader->SetMatrix4("u_ModelMatrix", modelMatrix);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene()
    {}
}
