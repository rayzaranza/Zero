#include "IndexBuffer.OpenGL.h"
#include <glad/glad.h>

Zero::IndexBufferOpenGL::IndexBufferOpenGL(const Array<uint32_t>& indices) : m_Length{ indices.size() } {
  glCreateBuffers(1, &m_Id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Length * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
}

Zero::IndexBufferOpenGL::IndexBufferOpenGL(const uint32_t* indices, const uint32_t count) : m_Length{ count } {
  glCreateBuffers(1, &m_Id);
  glBindBuffer(GL_ARRAY_BUFFER, m_Id);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

Zero::IndexBufferOpenGL::IndexBufferOpenGL(const uint32_t size) {
  glCreateBuffers(1, &m_Id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

Zero::IndexBufferOpenGL::~IndexBufferOpenGL() {
  glDeleteBuffers(1, &m_Id);
}

void Zero::IndexBufferOpenGL::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void Zero::IndexBufferOpenGL::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

size_t Zero::IndexBufferOpenGL::GetLength() const {
  return m_Length;
}
