#include "Zero/Renderer/Buffer/VertexArray.OpenGL.h"
#include "Zero/Renderer/Buffer/VertexAttribute.h"

#include <glad/glad.h>


static uint32_t GetOpenGLTypeFromAttributeType(const Zero::VertexAttributeType type);


Zero::VertexArrayOpenGL::VertexArrayOpenGL()
{
    glCreateVertexArrays(1, &m_Id);
}


Zero::VertexArrayOpenGL::~VertexArrayOpenGL()
{
    glDeleteVertexArrays(1, &m_Id);
}


void Zero::VertexArrayOpenGL::Bind() const
{
    glBindVertexArray(m_Id);
}


void Zero::VertexArrayOpenGL::Unbind() const
{
    glBindVertexArray(0);
}


void Zero::VertexArrayOpenGL::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
    const VertexBufferLayout& layout{ vertexBuffer->GetLayout() };
    ZR_CORE_ASSERT(layout.GetAttributes().size(), "Vertex Buffer has no layout");
    glBindVertexArray(m_Id);
    vertexBuffer->Bind();

    int32_t location{ 0 };
    for (const VertexAttribute& attribute : layout)
    {
        const uint32_t type{ GetOpenGLTypeFromAttributeType(attribute.Type) };
        const void* offset{ reinterpret_cast<const void*>(static_cast<uintptr_t>(attribute.Offset)) };
        const int32_t isNormalized{ attribute.IsNormalized ? GL_TRUE : GL_FALSE };

        glEnableVertexAttribArray(location);

        switch (attribute.Type)
        {
            case VertexAttributeType::Int:
            case VertexAttributeType::Vector2i:
            case VertexAttributeType::Vector3i:
            case VertexAttributeType::Vector4i:
            case VertexAttributeType::Boolean:
            {
                glVertexAttribIPointer(location, attribute.ComponentCount, type, layout.GetStride(), offset);
                break;
            }

            default:
            {
                glVertexAttribPointer(location, attribute.ComponentCount, type, isNormalized, layout.GetStride(), offset);
                break;
            }
        }

        location++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}


void Zero::VertexArrayOpenGL::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_Id);
    indexBuffer->Bind();
    m_IndexBuffer = indexBuffer;
}


const Zero::Array<Zero::Ref<Zero::VertexBuffer>>& Zero::VertexArrayOpenGL::GetVertexBuffers() const
{
    return m_VertexBuffers;
}


const Zero::Ref<Zero::IndexBuffer>& Zero::VertexArrayOpenGL::GetIndexBuffer() const
{
    return m_IndexBuffer;
}


uint32_t GetOpenGLTypeFromAttributeType(const Zero::VertexAttributeType type)
{
    switch (type)
    {
        case Zero::VertexAttributeType::Boolean:  return GL_BOOL;

        case Zero::VertexAttributeType::Float:
        case Zero::VertexAttributeType::Vector2:
        case Zero::VertexAttributeType::Vector3:
        case Zero::VertexAttributeType::Vector4:
        case Zero::VertexAttributeType::Matrix3:
        case Zero::VertexAttributeType::Matrix4:  return GL_FLOAT;

        case Zero::VertexAttributeType::Int:
        case Zero::VertexAttributeType::Vector2i:
        case Zero::VertexAttributeType::Vector3i:
        case Zero::VertexAttributeType::Vector4i: return GL_INT;

        default:
        {
            ZR_CORE_ASSERT(false, "Unknown Vertex Attribute Type");
            return 0u;
        }
    }
}
