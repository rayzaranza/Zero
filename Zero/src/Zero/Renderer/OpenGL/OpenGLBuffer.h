#pragma once

#include "Zero/Renderer/Buffer.h"

namespace Zero
{
    //======================================================================================
    //  OpenGL Verter Buffer
    //======================================================================================
    class OpenGLVertexBuffer : public VertexBuffer
    {
      public:
        OpenGLVertexBuffer(const uint32_t size);
        OpenGLVertexBuffer(const Array<float>& vertices);
        virtual ~OpenGLVertexBuffer();

      public:
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetData(const void* data, const uint32_t size) override;

      public:
        inline virtual void SetLayout(const VertexBufferLayout& layout) override { m_Layout = layout; }
        inline virtual const VertexBufferLayout& GetLayout() const override { return m_Layout; }

      private:
        uint32_t m_Id{};
        VertexBufferLayout m_Layout{};
    };

    //======================================================================================
    //  OpenGL Index Buffer
    //======================================================================================
    class OpenGLIndexBuffer : public IndexBuffer
    {
      public:
        OpenGLIndexBuffer(const uint32_t count);
        OpenGLIndexBuffer(const Array<uint32_t>& indices);
        OpenGLIndexBuffer(const uint32_t* indices, const uint32_t count);
        virtual ~OpenGLIndexBuffer();

      public:
        virtual void Bind() const override;
        virtual void Unbind() const override;

      public:
        inline virtual size_t GetLength() const override { return m_Length; }

      private:
        uint32_t m_Id{};
        size_t m_Length;
    };
}
