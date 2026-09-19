#include "VertexBufferLayout.h"

Zero::VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexAttribute>& attributes) : m_Attributes{ attributes } {
  CalculateOffsetsAndStride();
}

uint32_t Zero::VertexBufferLayout::GetStride() const {
  return m_Stride;
}

const Zero::Array<Zero::VertexAttribute>& Zero::VertexBufferLayout::GetAttributes() const {
  return m_Attributes;
}

Zero::Array<Zero::VertexAttribute>::iterator Zero::VertexBufferLayout::begin() {
  return m_Attributes.begin();
}

Zero::Array<Zero::VertexAttribute>::iterator Zero::VertexBufferLayout::end() {
  return m_Attributes.end();
}

Zero::Array<Zero::VertexAttribute>::const_iterator Zero::VertexBufferLayout::begin() const {
  return m_Attributes.begin();
}

Zero::Array<Zero::VertexAttribute>::const_iterator Zero::VertexBufferLayout::end() const {
  return m_Attributes.end();
}

void Zero::VertexBufferLayout::CalculateOffsetsAndStride() {
  uint32_t offset{ 0 };
  m_Stride = 0;
  for (VertexAttribute& attribute : m_Attributes) {
    attribute.Offset = offset;
    offset += attribute.Size;
    m_Stride += attribute.Size;
  }
}
