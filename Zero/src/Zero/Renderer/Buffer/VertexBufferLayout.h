#pragma once
#include "Zero/Renderer/Buffer/VertexAttribute.h"


namespace Zero {


class VertexBufferLayout
{
  public:
    VertexBufferLayout(const std::initializer_list<VertexAttribute>& attributes);

  public:
    uint32_t GetStride() const;
    const Array<VertexAttribute>& GetAttributes() const;

  public:
    Array<VertexAttribute>::iterator begin();
    Array<VertexAttribute>::iterator end();
    Array<VertexAttribute>::const_iterator begin() const;
    Array<VertexAttribute>::const_iterator end() const;

  private:
    void CalculateOffsetsAndStride();

  private:
    Array<VertexAttribute> m_Attributes;
    uint32_t m_Stride{};
};

}
