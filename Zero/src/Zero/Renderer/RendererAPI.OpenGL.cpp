#include "RendererAPI.OpenGL.h"
#include <glad/glad.h>

void Zero::RendererAPIOpenGL::Initialize() {
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Zero::RendererAPIOpenGL::SetClearColor(const glm::vec4& color) const {
  glClearColor(color.r, color.g, color.b, color.a);
}

void Zero::RendererAPIOpenGL::Clear() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Zero::RendererAPIOpenGL::Clear(const glm::vec4& color) const {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Zero::RendererAPIOpenGL::DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t indexCount) {
  const uint32_t count{ indexCount ? indexCount : static_cast<uint32_t>(vertexArray->GetIndexBuffer()->GetLength()) };
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Zero::RendererAPIOpenGL::SetViewport(const glm::ivec2& position, const glm::uvec2& size) {
  glViewport(position.x, position.y, size.x, size.y);
}
