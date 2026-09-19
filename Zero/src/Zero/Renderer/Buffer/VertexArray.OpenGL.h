#pragma once
#include "VertexArray.h"

namespace Zero {
  class VertexArrayOpenGL : public VertexArray {
  public:
    VertexArrayOpenGL();
    virtual ~VertexArrayOpenGL() override;
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
    virtual const Array<Ref<VertexBuffer>>& GetVertexBuffers() const override;
    virtual const Ref<IndexBuffer>& GetIndexBuffer() const override;

  private:
    uint32_t m_Id{};
    Array<Ref<VertexBuffer>> m_VertexBuffers{};
    Ref<IndexBuffer> m_IndexBuffer{};
  };
}
