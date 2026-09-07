#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    void Renderer::BeginScene()
    {}

    void Renderer::EndScene()
    {}

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    RendererAPI::API Renderer::GetAPI()
    {
        return RendererAPI::GetAPI();
    }
}
