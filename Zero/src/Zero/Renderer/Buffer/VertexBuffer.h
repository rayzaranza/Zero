#pragma once
#include "VertexAttribute.h"
#include "VertexBufferLayout.h"
#include "Zero/Core/Core.h"

namespace Zero {
  class VertexBuffer {
  public:
    virtual ~VertexBuffer() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void SetData(const void* data, const uint32_t size) = 0;
    virtual void SetLayout(const VertexBufferLayout& layout) = 0;
    virtual const VertexBufferLayout& GetLayout() const = 0;
    static Ref<VertexBuffer> Create(const Array<float>& vertices);
    static Ref<VertexBuffer> Create(const uint32_t size);
  };
}
