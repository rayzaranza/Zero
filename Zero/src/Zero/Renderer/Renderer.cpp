#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    void Renderer::BeginScene(const Camera& camera)
    {}

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene()
    {}
}
