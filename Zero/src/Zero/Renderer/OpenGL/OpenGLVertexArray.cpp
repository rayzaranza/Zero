#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Zero
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_Id);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_Id);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_Id);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    static U32 GetOpenGLTypeFromAttributeType(const AttributeType type);

    void OpenGLVertexArray::AddVertexBuffer(const VertexBufferRef& vertexBuffer)
    {
        const VertexBufferLayout& layout{ vertexBuffer->GetLayout() };
        ZR_CORE_ASSERT(layout.GetAttributes().size(), "Vertex Buffer has no layout");

        glBindVertexArray(m_Id);
        vertexBuffer->Bind();

        I32 location{ 0 };
        for (const VertexAttribute& attribute : layout)
        {
            glEnableVertexAttribArray(location);
            glVertexAttribPointer(
                location,
                attribute.ComponentCount,
                GetOpenGLTypeFromAttributeType(attribute.Type),
                attribute.IsNormalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(attribute.Offset))
            );
            ++location;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const IndexBufferRef& indexBuffer)
    {
        glBindVertexArray(m_Id);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }

    const Array<VertexBufferRef>& OpenGLVertexArray::GetVertexBuffers() const
    {
        return m_VertexBuffers;
    }

    const IndexBufferRef& OpenGLVertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }

    U32 GetOpenGLTypeFromAttributeType(const AttributeType type)
    {
        switch (type)
        {
            case AttributeType::Float:
            case AttributeType::Vector2:
            case AttributeType::Vector3:
            case AttributeType::Vector4:
            case AttributeType::Matrix3:
            case AttributeType::Matrix4:  return GL_FLOAT;

            case AttributeType::Int:
            case AttributeType::Vector2i:
            case AttributeType::Vector3i:
            case AttributeType::Vector4i: return GL_INT;

            case AttributeType::Boolean:  return GL_BOOL;

            default:
            {
                ZR_CORE_ASSERT(false, "Unknown Vertex Attribute Type");
                return 0;
            }
        }
    }
}
