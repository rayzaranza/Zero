#pragma once
#include "IndexBuffer.h"

namespace Zero {
  class IndexBufferOpenGL : public IndexBuffer {
  public:
    IndexBufferOpenGL(const uint32_t count);
    IndexBufferOpenGL(const Array<uint32_t>& indices);
    IndexBufferOpenGL(const uint32_t* indices, const uint32_t count);
    virtual ~IndexBufferOpenGL();
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual size_t GetLength() const override;

  private:
    uint32_t m_Id{};
    size_t m_Length;
  };
}
