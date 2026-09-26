#include "Sandbox2D.h"
#include <imgui.h>

Sandbox2D::Sandbox2D() : Zero::Layer{ "Sandbox2D" }, m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() } {
}

Sandbox2D::~Sandbox2D() {
}

void Sandbox2D::OnAttach() {
  m_Texture = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg");
  m_TextureCheckerboard = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/Checkerboard.png");
  // m_Quads = {
  //   { .Position{ -0.5f, 0.0f }, .Rotation{ glm::radians(45.0f) }, .Scale{ 0.5f }, .Color{ 0.8f, 0.2f, 0.3f, 1.0f } },
  //   { .Position{ -1.1f, -0.5f }, .Scale{ 0.2f } },
  //   { .Position{ 0.5f, -0.2f }, .Scale{ 1.0f }, .Color{ 0.1f, 0.4f, 0.1f, 1.0f } },
  //   { .Position{ 0.5f, -0.5f }, .Scale{ 0.5f, 0.75f }, .Texture{ m_Texture } },
  // };
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(const Zero::DeltaTime deltaTime) {
  // m_Quads[1].Rotation += deltaTime * 2.0f;
  m_CameraController.OnUpdate(deltaTime);
}

void Sandbox2D::OnRender() {
  Zero::Renderer2D::ResetStats();

  Zero::RenderCommand::Clear({ 0.02f, 0.02f, 0.022f, 1.0f });

  Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
  for (float y{ -5.0f }; y < 5.0f; y += 0.1f) {
    for (float x{ -5.0f }; x < 5.0f; x += 0.1f) {
      // Zero::Renderer2D::DrawQuad({ .Position{ x, y }, .Scale{ 0.09f }, .Color{ (x + 5.0f) / 10.0f, 0.0f, (y + 5.0f) / 10.0f, 1.0f } });
    }
  }
  for (const auto& quad : m_Quads) {
    Zero::Renderer2D::DrawQuad(quad);
  }

  Zero::Renderer2D::EndScene();
}

void Sandbox2D::OnUIRender() {
  const Zero::RenderStats& stats{ Zero::Renderer2D::GetStats() };
  ImGui::Begin("Settings");
  ImGui::Text("Renderer2D Stats");
  ImGui::Text("Draw Calls: %d", stats.DrawCalls);
  ImGui::Text("Quads: %d", stats.QuadCount);
  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
  ImGui::End();
}

void Sandbox2D::OnEvent(Zero::Event& event) {
  m_CameraController.OnEvent(event);
  Zero::EventDispatcher dispatcher{ event };
  dispatcher.Dispatch<Zero::KeyPressedEvent>(ZR_BIND_FUNCTION(Sandbox2D::OnKeyPressed));
}

bool Sandbox2D::OnKeyPressed(Zero::KeyPressedEvent& event) {
  if (event.GetKeyCode() == Zero::KeyCode::ESCAPE) {
    Zero::Application::Get().Close();
    return true;
  }
  return false;
}
