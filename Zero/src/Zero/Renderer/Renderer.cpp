#include "Renderer.h"
#include "Renderer2D.h"

Zero::Scope<Zero::Renderer::SceneData> Zero::Renderer::s_SceneData{ CreateScope<SceneData>() };

Zero::RendererAPI::API Zero::Renderer::GetAPI() {
  return RendererAPI::GetAPI();
}

void Zero::Renderer::Initialize() {
  RenderCommand::Initialize();
  Renderer2D::Initialize();
}

void Zero::Renderer::Destroy() {
  Renderer2D::Destroy();
}

void Zero::Renderer::OnWindowResized(const glm::uvec2& size) {
  RenderCommand::SetViewport({ 0, 0 }, size);
}

void Zero::Renderer::BeginScene(CameraOrthographic& camera) {
  s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Zero::Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& modelMatrix) {
  shader->Bind();
  shader->SetMatrix4("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
  shader->SetMatrix4("u_ModelMatrix", modelMatrix);
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

void Zero::Renderer::EndScene() {
}
