#include "Zero/Renderer/Renderer.h"

#include "Zero/Renderer/Renderer2D.h"

namespace Zero
{
    Renderer::SceneData* Renderer::s_SceneData{ new Renderer::SceneData() };

    void Renderer::Initialize()
    {
        RenderCommand::Initialize();
        Renderer2D::Initialize();
    }

    void Renderer::OnWindowResized(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& modelMatrix)
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
