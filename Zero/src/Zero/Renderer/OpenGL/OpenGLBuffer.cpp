#include "Zero/Renderer/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Zero
{
    //=================================================================================================================
    //  OpenGL Vertex Buffer
    //=================================================================================================================
    OpenGLVertexBuffer::OpenGLVertexBuffer(const U32 size)
    {
        ZR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(const Array<F32>& vertices)
    {
        ZR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(F32), vertices.data(), GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        ZR_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_Id);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        ZR_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        ZR_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(const void* data, const U32 size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    //=================================================================================================================
    //  OpenGL Index Buffer
    //=================================================================================================================
    OpenGLIndexBuffer::OpenGLIndexBuffer(const Array<U32>& indices) : m_Length{ indices.size() }
    {
        ZR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Length * sizeof(U32), indices.data(), GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(const U32* indices, const U32 size)
    {
        ZR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(const U32 size)
    {
        ZR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        ZR_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_Id);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        ZR_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        ZR_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}
