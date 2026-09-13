#include "Zero/Renderer/RendererAPI.h"

#include "Zero/Renderer/OpenGL/OpenGLRendererAPI.h";

namespace Zero
{
    RendererAPI::API RendererAPI::s_API{ RendererAPI::API::OpenGL };

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
            case API::None:   ZR_CORE_ASSERT(false, "Renderer API None is not supported"); return nullptr;
            case API::Vulkan: ZR_CORE_ASSERT(false, "Renderer API Vulkan is not supported"); return nullptr;
            case API::OpenGL: return CreateScope<OpenGLRendererAPI>();
        }

        ZR_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
}
