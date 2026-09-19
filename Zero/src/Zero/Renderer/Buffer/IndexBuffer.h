#pragma once
#include "Zero/Core/Core.h"

namespace Zero {
  class IndexBuffer {
  public:
    virtual ~IndexBuffer() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual size_t GetLength() const = 0;
    static Ref<IndexBuffer> Create(const uint32_t size);
    static Ref<IndexBuffer> Create(const uint32_t* indices, const uint32_t count);
    static Ref<IndexBuffer> Create(const Array<uint32_t>& indices);
  };
}
