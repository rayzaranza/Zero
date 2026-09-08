#include "Zero/Renderer/Buffer.h"
#include "Zero/Renderer/OpenGL/OpenGLBuffer.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{

    // ················································································································
    //  Vertex Buffer Layout
    // ················································································································

    void VertexBufferLayout::CalculateOffsetsAndStride()
    {
        uint32_t offset { 0 };
        m_Stride = 0;

        for (VertexAttribute& attribute : m_Attributes)
        {
            attribute.Offset = offset;
            offset += attribute.Size;
            m_Stride += attribute.Size;
        }
    }

    // ················································································································
    //  Vertex Buffer
    // ················································································································

    VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
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
                return new OpenGLVertexBuffer(vertices, size);
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

    // ················································································································
    //  Index Buffer
    // ················································································································

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, size_t size)
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
                return new OpenGLIndexBuffer(indices, size);
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

    // ················································································································
    //  Vertex Attribute Type Helpers
    // ················································································································

    uint32_t GetSizeFromAttributeType(AttributeType type)
    {
        switch (type)
        {
            case AttributeType::Float:   return 4;
            case AttributeType::Float2:  return 4 * 2;
            case AttributeType::Float3:  return 4 * 3;
            case AttributeType::Float4:  return 4 * 4;
            case AttributeType::Matrix3: return 4 * 3 * 3;
            case AttributeType::Matrix4: return 4 * 4 * 4;
            case AttributeType::Int:     return 4;
            case AttributeType::Int2:    return 4 * 2;
            case AttributeType::Int3:    return 4 * 3;
            case AttributeType::Int4:    return 4 * 4;
            case AttributeType::Boolean: return 1;

            default:
            {
                ZERO_CORE_ASSERT(false, "Unknow Vertex Attribute Type");
                return 0;
            }
        }
    }

    uint32_t GetComponentCountFromAttributeType(AttributeType type)
    {
        switch (type)
        {
            case AttributeType::Float:   return 1;
            case AttributeType::Float2:  return 2;
            case AttributeType::Float3:  return 3;
            case AttributeType::Float4:  return 4;
            case AttributeType::Matrix3: return 3 * 3;
            case AttributeType::Matrix4: return 4 * 4;
            case AttributeType::Int:     return 1;
            case AttributeType::Int2:    return 2;
            case AttributeType::Int3:    return 3;
            case AttributeType::Int4:    return 4;
            case AttributeType::Boolean: return 1;

            default:
            {
                ZERO_CORE_ASSERT(false, "Unknow Vertex Attribute Type");
                return 0;
            }
        }
    }
}
