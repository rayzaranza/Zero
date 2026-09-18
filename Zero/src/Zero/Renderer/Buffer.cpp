#include "Zero/Renderer/Buffer.h"

#include "Zero/Renderer/OpenGL/OpenGLBuffer.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    //======================================================================================
    //  Vertex Buffer Layout
    //======================================================================================
    void VertexBufferLayout::CalculateOffsetsAndStride()
    {
        uint32_t offset{ 0 };
        m_Stride = 0;

        for (VertexAttribute& attribute : m_Attributes)
        {
            attribute.Offset = offset;
            offset += attribute.Size;
            m_Stride += attribute.Size;
        }
    }

    //======================================================================================
    //  Vertex Buffer
    //======================================================================================
    VertexBufferRef VertexBuffer::Create(const Array<float>& vertices)
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
                return CreateRef<OpenGLVertexBuffer>(vertices);
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

    VertexBufferRef VertexBuffer::Create(const uint32_t size)
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
                return CreateRef<OpenGLVertexBuffer>(size);
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

    //======================================================================================
    //  Index Buffer
    //======================================================================================
    Ref<IndexBuffer> IndexBuffer::Create(const Array<uint32_t>& indices)
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
                return CreateRef<OpenGLIndexBuffer>(indices);
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

    Ref<IndexBuffer> IndexBuffer::Create(const uint32_t size)
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
                return CreateRef<OpenGLIndexBuffer>(size);
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

    Ref<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, const uint32_t size)
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
                return CreateRef<OpenGLIndexBuffer>(indices, size);
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

    //======================================================================================
    //  Vertex Attribute Type Helpers
    //======================================================================================
    int32_t GetSizeFromAttributeType(const AttributeType type)
    {
        switch (type)
        {
            case AttributeType::Float:    return 4;
            case AttributeType::Vector2:  return 4 * 2;
            case AttributeType::Vector3:  return 4 * 3;
            case AttributeType::Vector4:  return 4 * 4;
            case AttributeType::Matrix3:  return 4 * 3 * 3;
            case AttributeType::Matrix4:  return 4 * 4 * 4;
            case AttributeType::Int:      return 4;
            case AttributeType::Vector2i: return 4 * 2;
            case AttributeType::Vector3i: return 4 * 3;
            case AttributeType::Vector4i: return 4 * 4;
            case AttributeType::Boolean:  return 1;

            default:
            {
                ZR_CORE_ASSERT(false, "Unknow Vertex Attribute Type");
                return 0;
            }
        }
    }

    uint32_t GetComponentCountFromAttributeType(const AttributeType type)
    {
        switch (type)
        {
            case AttributeType::Float:    return 1;
            case AttributeType::Vector2:  return 2;
            case AttributeType::Vector3:  return 3;
            case AttributeType::Vector4:  return 4;
            case AttributeType::Matrix3:  return 3 * 3;
            case AttributeType::Matrix4:  return 4 * 4;
            case AttributeType::Int:      return 1;
            case AttributeType::Vector2i: return 2;
            case AttributeType::Vector3i: return 3;
            case AttributeType::Vector4i: return 4;
            case AttributeType::Boolean:  return 1;

            default:
            {
                ZR_CORE_ASSERT(false, "Unknow Vertex Attribute Type");
                return 0;
            }
        }
    }
}
