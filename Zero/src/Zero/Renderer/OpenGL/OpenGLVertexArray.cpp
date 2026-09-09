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

    static GLenum GetOpenGLTypeFromAttributeType(AttributeType type);

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        const VertexBufferLayout& layout{vertexBuffer->GetLayout()};
        ZERO_CORE_ASSERT(layout.GetAttributes().size(), "Vertex Buffer has no layout");

        glBindVertexArray(m_Id);
        vertexBuffer->Bind();

        int location{0};
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

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_Id);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }

    const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
    {
        return m_VertexBuffers;
    }

    const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }

    GLenum GetOpenGLTypeFromAttributeType(AttributeType type)
    {
        switch (type)
        {
            case AttributeType::Float:
            case AttributeType::Float2:
            case AttributeType::Float3:
            case AttributeType::Float4:
            case AttributeType::Matrix3:
            case AttributeType::Matrix4: return GL_FLOAT;

            case AttributeType::Int:
            case AttributeType::Int2:
            case AttributeType::Int3:    return GL_INT;

            case AttributeType::Boolean: return GL_BOOL;

            default:
            {
                ZERO_CORE_ASSERT(false, "Unknown Vertex Attribute Type");
                return 0;
            }
        }
    }
}
