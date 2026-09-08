#include "Zero/Renderer/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Zero
{
    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) const
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}
