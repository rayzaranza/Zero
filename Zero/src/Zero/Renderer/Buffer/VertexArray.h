#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace Zero {
  class VertexArray {
  public:
    virtual ~VertexArray() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
    virtual const Array<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
    virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
    static Ref<VertexArray> Create();
  };
}
