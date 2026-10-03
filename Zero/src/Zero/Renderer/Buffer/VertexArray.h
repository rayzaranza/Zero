#pragma once
#include "Zero/Renderer/Buffer/IndexBuffer.h"
#include "Zero/Renderer/Buffer/VertexBuffer.h"


namespace Zero {


class VertexArray
{
  public:
    virtual ~VertexArray() = default;

  public:
    static Ref<VertexArray> Create();

  public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
    virtual const Array<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
    virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
};


}
