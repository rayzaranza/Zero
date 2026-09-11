#pragma once

#include "Zero/Renderer/VertexArray.h"

namespace Zero
{
    class OpenGLVertexArray : public VertexArray
    {
      public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() override;

      public:
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void AddVertexBuffer(const VertexBufferRef& vertexBuffer) override;
        virtual void SetIndexBuffer(const IndexBufferRef& indexBuffer) override;
        virtual const Array<VertexBufferRef>& GetVertexBuffers() const override;
        virtual const IndexBufferRef& GetIndexBuffer() const override;

      private:
        RendererID m_Id{};
        Array<VertexBufferRef> m_VertexBuffers{};
        IndexBufferRef m_IndexBuffer{};
    };
}
