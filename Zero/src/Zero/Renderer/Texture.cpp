#include "Zero/Renderer/Texture.h"

#include "Zero/Core.h"
#include "Zero/Renderer/OpenGL/OpenGLTexture.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    Ref<Texture2D> Texture2D::Create(const std::string& path)
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
                return std::make_shared<OpenGLTexture2D>(path);
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
}
