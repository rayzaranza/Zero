#include "Zero/Renderer/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Zero
{
    void OpenGLRendererAPI::Initialize()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::SetClearColor(const Color& color) const
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const VertexArrayRef& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetLength(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::SetViewport(I32 x, I32 y, U32 width, U32 height)
    {
        glViewport(x, y, width, height);
    }
}
