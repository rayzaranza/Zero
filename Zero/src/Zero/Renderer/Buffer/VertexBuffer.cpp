#include "Zero/Renderer/Buffer/VertexBuffer.h"
#include "Zero/Renderer/Buffer/VertexBuffer.OpenGL.h"
#include "Zero/Renderer/Renderer.h"


Zero::Ref<Zero::VertexBuffer> Zero::VertexBuffer::Create(const Array<float>& vertices)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
        {
            return CreateRef<VertexBufferOpenGL>(vertices);
        }

        case RendererAPI::API::None:
        {
            ZR_CORE_ASSERT(false, "Renderer API set to None");
            return nullptr;
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


Zero::Ref<Zero::VertexBuffer> Zero::VertexBuffer::Create(const uint32_t size)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
        {
            return CreateRef<VertexBufferOpenGL>(size);
        }

        case RendererAPI::API::None:
        {
            ZR_CORE_ASSERT(false, "Renderer API set to None");
            return nullptr;
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
