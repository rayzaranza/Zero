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
        U32 offset{ 0 };
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
    VertexBufferRef VertexBuffer::Create(const Array<F32>& vertices)
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

    //======================================================================================
    //  Index Buffer
    //======================================================================================
    IndexBufferRef IndexBuffer::Create(const Array<U32>& indices)
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

    //======================================================================================
    //  Vertex Attribute Type Helpers
    //======================================================================================
    I32 GetSizeFromAttributeType(AttributeType type)
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

    U32 GetComponentCountFromAttributeType(AttributeType type)
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
