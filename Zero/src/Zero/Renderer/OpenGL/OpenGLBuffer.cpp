#include "Zero/Renderer/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Zero
{
    //=================================================================================================================
    //  OpenGL Vertex Buffer
    //=================================================================================================================
    OpenGLVertexBuffer::OpenGLVertexBuffer(const uint32_t size)
    {
        ZR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(const Array<float>& vertices)
    {
        ZR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
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

    void OpenGLVertexBuffer::SetData(const void* data, const uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    //=================================================================================================================
    //  OpenGL Index Buffer
    //=================================================================================================================
    OpenGLIndexBuffer::OpenGLIndexBuffer(const Array<uint32_t>& indices) : m_Length{ indices.size() }
    {
        ZR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Length * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, const uint32_t count) : m_Length{ count }
    {
        ZR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t size)
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
