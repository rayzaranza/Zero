#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace Zero
{
    RendererAPI* RenderCommand::s_RendererAPI { new OpenGLRendererAPI() };

    void RenderCommand::Clear()
    {
        s_RendererAPI->Clear();
    }

    void RenderCommand::SetClearColor(const glm::vec4& color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        s_RendererAPI->DrawIndexed(vertexArray);
    }
}
