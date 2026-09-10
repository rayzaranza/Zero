#include "Zero/Renderer/Shader.h"

#include "Zero/Renderer/OpenGL/OpenGLShader.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    Ref<Shader> Shader::Create(const std::string& filePath)
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
                return std::make_shared<OpenGLShader>(filePath);
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

    Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
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
                return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
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
