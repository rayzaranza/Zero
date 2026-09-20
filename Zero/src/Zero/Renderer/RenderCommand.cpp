#include "RenderCommand.h"

Zero::Scope<Zero::RendererAPI> Zero::RenderCommand::s_RendererAPI{ RendererAPI::Create() };

void Zero::RenderCommand::Initialize() {
  s_RendererAPI->Initialize();
}

void Zero::RenderCommand::Clear() {
  s_RendererAPI->Clear();
}

void Zero::RenderCommand::SetClearColor(const glm::vec4& color) {
  s_RendererAPI->SetClearColor(color);
}

void Zero::RenderCommand::Clear(const glm::vec4& color) {
  s_RendererAPI->Clear(color);
}

void Zero::RenderCommand::SetViewport(const glm::ivec2& position, const glm::uvec2& size) {
  s_RendererAPI->SetViewport(position, size);
}

void Zero::RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t indexCount) {
  s_RendererAPI->DrawIndexed(vertexArray, indexCount);
}
