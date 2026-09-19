#pragma once
#include "VertexBuffer.h"

namespace Zero {
  class VertexBufferOpenGL : public VertexBuffer {
  public:
    VertexBufferOpenGL(const uint32_t size);
    VertexBufferOpenGL(const Array<float>& vertices);
    virtual ~VertexBufferOpenGL();
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void SetData(const void* data, const uint32_t size) override;
    virtual void SetLayout(const VertexBufferLayout& layout) override;
    virtual const VertexBufferLayout& GetLayout() const override;

  private:
    uint32_t m_Id{};
    VertexBufferLayout m_Layout{};
  };
}
