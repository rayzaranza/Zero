#include "Zero/Renderer/VertexArray.h"

#include "Zero/Renderer/OpenGL/OpenGLVertexArray.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
            {
                ZERO_CORE_ASSERT(false, "Renderer API set to None");
                return nullptr;
            }
            case RendererAPI::API::OpenGL:
            {
                return new OpenGLVertexArray();
            }
            case RendererAPI::API::Vulkan:
            {
                ZERO_CORE_ASSERT(false, "Vulkan Renderer API not supported");
                return nullptr;
            }
            default:
            {
                ZERO_CORE_ASSERT(false, "Unknown Renderer API");
                return nullptr;
            }
        }
    }
}
