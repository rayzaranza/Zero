#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    Renderer::SceneData* Renderer::s_SceneData { new Renderer::SceneData() };

    void Renderer::BeginScene(CameraOrthographic& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
    {
        shader->Bind();
        shader->SetUniform("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene()
    {}
}
