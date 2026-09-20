#include "VertexBuffer.OpenGL.h"
#include <glad/glad.h>

Zero::VertexBufferOpenGL::VertexBufferOpenGL(const uint32_t size) {
  glCreateBuffers(1, &m_Id);
  glBindBuffer(GL_ARRAY_BUFFER, m_Id);
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

Zero::VertexBufferOpenGL::VertexBufferOpenGL(const Array<float>& vertices) {
  glCreateBuffers(1, &m_Id);
  glBindBuffer(GL_ARRAY_BUFFER, m_Id);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

Zero::VertexBufferOpenGL::~VertexBufferOpenGL() {
  glDeleteBuffers(1, &m_Id);
}

void Zero::VertexBufferOpenGL::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void Zero::VertexBufferOpenGL::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Zero::VertexBufferOpenGL::SetData(const void* data, const uint32_t size) {
  glBindBuffer(GL_ARRAY_BUFFER, m_Id);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void Zero::VertexBufferOpenGL::SetLayout(const VertexBufferLayout& layout) {
  m_Layout = layout;
}

const Zero::VertexBufferLayout& Zero::VertexBufferOpenGL::GetLayout() const {
  return m_Layout;
}
