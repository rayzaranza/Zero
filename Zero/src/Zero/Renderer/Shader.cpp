#include "Zero/Renderer/Shader.h"

#include "Zero/Renderer/OpenGL/OpenGLShader.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    ShaderRef Shader::Create(const String& filePath)
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
                return CreateRef<OpenGLShader>(filePath);
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

    ShaderRef Shader::Create(const String& name, const String& vertexSource, const String& fragmentSource)
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
                return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
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

    void ShaderLibrary::Add(const String& name, const ShaderRef& shader)
    {
        ZR_CORE_ASSERT(!Exists(name), "Shader already exists");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const ShaderRef& shader)
    {
        const String& name{ shader->GetName() };
        Add(name, shader);
    }

    ShaderRef ShaderLibrary::Load(const String& filePath)
    {
        ShaderRef shader{ Shader::Create(filePath) };
        Add(shader);
        return shader;
    }

    ShaderRef ShaderLibrary::Load(const String& name, const String& filePath)
    {
        ShaderRef shader{ Shader::Create(filePath) };
        Add(name, shader);
        return shader;
    }

    ShaderRef ShaderLibrary::Get(const String& name)
    {
        ZR_CORE_ASSERT(Exists(name), "Shader not found");
        return m_Shaders[name];
    }

    Boolean ShaderLibrary::Exists(const String& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }

    ShaderLibraryRef ShaderLibrary::Create()
    {
        return CreateRef<ShaderLibrary>();
    }
}
