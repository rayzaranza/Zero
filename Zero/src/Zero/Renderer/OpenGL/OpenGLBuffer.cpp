#include "Zero/Renderer/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Zero
{
    //=================================================================================================================
    //  OpenGL Vertex Buffer
    //=================================================================================================================
    OpenGLVertexBuffer::OpenGLVertexBuffer(const Array<F32>& vertices)
    {
        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(F32), vertices.data(), GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_Id);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetLayout(const VertexBufferLayout& layout)
    {
        m_Layout = layout;
    }

    const VertexBufferLayout& OpenGLVertexBuffer::GetLayout() const
    {
        return m_Layout;
    }

    //=================================================================================================================
    //  OpenGL Index Buffer
    //=================================================================================================================
    OpenGLIndexBuffer::OpenGLIndexBuffer(const Array<U32>& indices) : m_Length{ indices.size() }
    {
        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Length * sizeof(U32), indices.data(), GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_Id);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Length OpenGLIndexBuffer::GetLength() const
    {
        return m_Length;
    }
}
