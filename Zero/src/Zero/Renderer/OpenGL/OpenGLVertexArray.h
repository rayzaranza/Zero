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
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

      private:
        uint32_t m_Id {};
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers {};
        std::shared_ptr<IndexBuffer> m_IndexBuffer {};
    };
}
