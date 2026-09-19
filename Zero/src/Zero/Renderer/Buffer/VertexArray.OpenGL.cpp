#include "VertexArray.OpenGL.h"
#include "VertexAttribute.h"
#include <glad/glad.h>

static uint32_t GetOpenGLTypeFromAttributeType(const Zero::VertexAttributeType type);

Zero::VertexArrayOpenGL::VertexArrayOpenGL() {
  glCreateVertexArrays(1, &m_Id);
}

Zero::VertexArrayOpenGL::~VertexArrayOpenGL() {
  glDeleteVertexArrays(1, &m_Id);
}

void Zero::VertexArrayOpenGL::Bind() const {
  glBindVertexArray(m_Id);
}

void Zero::VertexArrayOpenGL::Unbind() const {
  glBindVertexArray(0);
}

void Zero::VertexArrayOpenGL::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
  const VertexBufferLayout& layout{ vertexBuffer->GetLayout() };
  ZR_CORE_ASSERT(layout.GetAttributes().size(), "Vertex Buffer has no layout");
  glBindVertexArray(m_Id);
  vertexBuffer->Bind();

  int32_t location{ 0 };
  for (const VertexAttribute& attribute : layout) {
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(
      location,
      attribute.ComponentCount,
      GetOpenGLTypeFromAttributeType(attribute.Type),
      attribute.IsNormalized ? GL_TRUE : GL_FALSE,
      layout.GetStride(),
      reinterpret_cast<const void*>(static_cast<uintptr_t>(attribute.Offset))
    );
    location++;
  }

  m_VertexBuffers.push_back(vertexBuffer);
}

void Zero::VertexArrayOpenGL::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
  glBindVertexArray(m_Id);
  indexBuffer->Bind();
  m_IndexBuffer = indexBuffer;
}

const Zero::Array<Zero::Ref<Zero::VertexBuffer>>& Zero::VertexArrayOpenGL::GetVertexBuffers() const {
  return m_VertexBuffers;
}

const Zero::Ref<Zero::IndexBuffer>& Zero::VertexArrayOpenGL::GetIndexBuffer() const {
  return m_IndexBuffer;
}

uint32_t GetOpenGLTypeFromAttributeType(const Zero::VertexAttributeType type) {
  switch (type) {
    case Zero::VertexAttributeType::Float:
    case Zero::VertexAttributeType::Vector2:
    case Zero::VertexAttributeType::Vector3:
    case Zero::VertexAttributeType::Vector4:
    case Zero::VertexAttributeType::Matrix3:
    case Zero::VertexAttributeType::Matrix4:  return GL_FLOAT;
    case Zero::VertexAttributeType::Int:
    case Zero::VertexAttributeType::Vector2i:
    case Zero::VertexAttributeType::Vector3i:
    case Zero::VertexAttributeType::Vector4i: return GL_INT;
    case Zero::VertexAttributeType::Boolean:  return GL_BOOL;
  }
  ZR_CORE_ASSERT(false, "Unknown Vertex Attribute Type");
  return 0;
}
