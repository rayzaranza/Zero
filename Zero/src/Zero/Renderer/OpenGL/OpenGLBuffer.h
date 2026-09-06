#pragma once

#include "Zero/Renderer/Buffer.h"

namespace Zero
{
    // ················································································································
    //  OpenGL Verter Buffer
    // ················································································································

    class OpenGLVertexBuffer : public VertexBuffer
    {
      public:
        OpenGLVertexBuffer(float* vertices, size_t size);
        virtual ~OpenGLVertexBuffer();

      public:
        virtual void Bind() const override;
        virtual void Unbind() const override;

      private:
        uint32_t m_Id {};
    };

    // ················································································································
    //  OpenGL Index Buffer
    // ················································································································

    class OpenGLIndexBuffer : public IndexBuffer
    {
      public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

      public:
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual uint32_t GetCount() const override;

      private:
        uint32_t m_Id {};
        uint32_t m_Count {};
    };
}
