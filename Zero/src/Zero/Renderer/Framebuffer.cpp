#include "Zero/Renderer/Framebuffer.h"
#include "Zero/Renderer/Framebuffer.OpenGL.h"
#include "Zero/Renderer/Renderer.h"


Zero::Ref<Zero::Framebuffer> Zero::Framebuffer::Create(const FramebufferProps& props)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
        {
            ZR_CORE_ASSERT(false, "Renderer API set to None");
            return nullptr;
        }

        case RendererAPI::API::OpenGL:
        {
            return CreateRef<FramebufferOpenGL>(props);
        }

        case RendererAPI::API::Vulkan:
        {
            ZR_CORE_ASSERT(false, "Vulkan Renderer API not supported");
            return nullptr;
        }

        default:
        {
            ZR_CORE_ASSERT(false, "Unknown Renderer API");
            return nullptr;
        }
    }
}
