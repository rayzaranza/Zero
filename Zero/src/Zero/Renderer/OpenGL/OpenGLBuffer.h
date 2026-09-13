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
        OpenGLVertexBuffer(const Array<F32>& vertices);
        virtual ~OpenGLVertexBuffer();

      public:
        virtual void Bind() const override;
        virtual void Unbind() const override;

      public:
        inline virtual void SetLayout(const VertexBufferLayout& layout) override { m_Layout = layout; }
        inline virtual const VertexBufferLayout& GetLayout() const override { return m_Layout; }

      private:
        RendererID m_Id{};
        VertexBufferLayout m_Layout{};
    };

    //======================================================================================
    //  OpenGL Index Buffer
    //======================================================================================
    class OpenGLIndexBuffer : public IndexBuffer
    {
      public:
        OpenGLIndexBuffer(const Array<U32>& indices);
        virtual ~OpenGLIndexBuffer();

      public:
        virtual void Bind() const override;
        virtual void Unbind() const override;

      public:
        inline virtual Length GetLength() const override { return m_Length; }

      private:
        RendererID m_Id{};
        Length m_Length;
    };
}
