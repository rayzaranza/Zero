#include "Zero/Renderer/RendererAPI.h"

namespace Zero
{
    RendererAPI::API RendererAPI::s_API { RendererAPI::API::OpenGL };

    RendererAPI::API RendererAPI::GetAPI()
    {
        return s_API;
    }
}
