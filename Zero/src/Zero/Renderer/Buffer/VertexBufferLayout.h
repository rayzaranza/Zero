#pragma once
#include "VertexAttribute.h"

namespace Zero {
  class VertexBufferLayout {
  public:
    VertexBufferLayout(const std::initializer_list<VertexAttribute>& attributes);
    uint32_t GetStride() const;
    const Array<VertexAttribute>& GetAttributes() const;
    Array<VertexAttribute>::iterator begin();
    Array<VertexAttribute>::iterator end();
    Array<VertexAttribute>::const_iterator begin() const;
    Array<VertexAttribute>::const_iterator end() const;

  private:
    void CalculateOffsetsAndStride();
    Array<VertexAttribute> m_Attributes;
    uint32_t m_Stride{};
  };
}
