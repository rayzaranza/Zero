#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    RendererAPI Renderer::s_RendererAPI { RendererAPI::OpenGL };

    RendererAPI Renderer::GetAPI()
    {
        return s_RendererAPI;
    }
}
