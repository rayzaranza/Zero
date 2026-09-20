#include "EditorLayer.h"
#include <imgui.h>

Zero::EditorLayer::EditorLayer() : Layer{ "EditorLayer" }, m_CameraController{ Application::Get().GetWindow().GetAspectRatio() } {
}

Zero::EditorLayer::~EditorLayer() {
}

void Zero::EditorLayer::OnAttach() {
  m_Texture = Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg");
  m_TextureCheckerboard = Texture2D::Create("D:/Zero/Sandbox/assets/textures/Checkerboard.png");
  m_Quads = {
    { .Position{ -0.5f, 0.0f }, .Rotation{ glm::radians(45.0f) }, .Scale{ 0.5f }, .Color{ 0.8f, 0.2f, 0.3f, 1.0f } },
    { .Position{ -1.1f, -0.5f }, .Scale{ 0.2f } },
    { .Position{ 0.5f, -0.2f }, .Scale{ 1.0f }, .Color{ 0.1f, 0.4f, 0.1f, 1.0f } },
    { .Position{ 0.5f, -0.5f }, .Scale{ 0.5f, 0.75f }, .Texture{ m_Texture } },
  };

  m_Framebuffer = Framebuffer::Create({ .Width{ 1280u }, .Height{ 720u } });
}

void Zero::EditorLayer::OnDetach() {
}

void Zero::EditorLayer::OnUpdate(const DeltaTime deltaTime) {
  m_Quads[1].Rotation += deltaTime * 2.0f;
  m_CameraController.OnUpdate(deltaTime);
}

void Zero::EditorLayer::OnRender() {
  Zero::Renderer2D::ResetStats();

  m_Framebuffer->Bind();
  Zero::RenderCommand::Clear({ 0.02f, 0.02f, 0.022f, 1.0f });

  Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
  for (float y{ -5.0f }; y < 5.0f; y += 0.1f) {
    for (float x{ -5.0f }; x < 5.0f; x += 0.1f) {
      Zero::Renderer2D::DrawQuad({ .Position{ x, y }, .Scale{ 0.09f }, .Color{ (x + 5.0f) / 10.0f, 0.0f, (y + 5.0f) / 10.0f, 1.0f } });
    }
  }
  for (const auto& quad : m_Quads) {
    Zero::Renderer2D::DrawQuad(quad);
  }

  Zero::Renderer2D::EndScene();
  m_Framebuffer->Unbind();
}

void Zero::EditorLayer::OnUIRender() {
  const RenderStats& stats{ Renderer2D::GetStats() };

  static bool isOpen{ true };
  static bool isFullscreenPersistant{ true };
  bool isFullscreen{ isFullscreenPersistant };
  static ImGuiDockNodeFlags dockSpaceFlags{ ImGuiDockNodeFlags_None };

  ImGuiWindowFlags windowFlags{ ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking };
  if (isFullscreen) {
    ImGuiViewport* viewport{ ImGui::GetMainViewport() };
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  }

  if (dockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
    windowFlags |= ImGuiWindowFlags_NoBackground;
  }

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
  ImGui::Begin("Zero DockSpace Demo", &isOpen, windowFlags);
  ImGui::PopStyleVar();

  if (isFullscreen) {
    ImGui::PopStyleVar(2);
  }

  ImGuiIO& io{ ImGui::GetIO() };
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGuiID dockSpaceId{ ImGui::GetID("ZeroDockSpace") };
    ImGui::DockSpace(dockSpaceId, ImVec2{ 0.0f, 0.0f }, dockSpaceFlags);
  }

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit")) {
        Application::Get().Close();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  ImGui::Begin("Settings");
  ImGui::Text("Renderer2D Stats");
  ImGui::Text("Draw Calls: %d", stats.DrawCalls);
  ImGui::Text("Quads: %d", stats.QuadCount);
  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

  ImGui::Image(m_Framebuffer->GetColorAttachmentRendererID(), ImVec2{ 1280.0f, 720.0f }, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
  ImGui::End();

  ImGui::End();
}

void Zero::EditorLayer::OnEvent(Event& event) {
  m_CameraController.OnEvent(event);
  EventDispatcher dispatcher{ event };
  dispatcher.Dispatch<Zero::KeyPressedEvent>(ZR_BIND_FUNCTION(EditorLayer::OnKeyPressed));
}

bool Zero::EditorLayer::OnKeyPressed(KeyPressedEvent& event) {
  if (event.GetKeyCode() == KeyCode::ESCAPE) {
    Application::Get().Close();
    return true;
  }
  return false;
}
