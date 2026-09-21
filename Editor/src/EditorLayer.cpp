#include "EditorLayer.h"

Zero::EditorLayer::EditorLayer() : Layer{ "EditorLayer" }, m_CameraController{ Application::Get().GetWindow().GetAspectRatio() } {
}

Zero::EditorLayer::~EditorLayer() {
}

void Zero::EditorLayer::OnAttach() {
  m_Texture = Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg");
  m_TextureCheckerboard = Texture2D::Create("D:/Zero/Sandbox/assets/textures/Checkerboard.png");
  m_Framebuffer = Framebuffer::Create({ .Size{ 1280u, 720u } });
  m_ActiveScene = CreateRef<Scene>();

  m_QuadEntity = m_ActiveScene->CreateEntity();
  m_ActiveScene->GetRegistry().emplace<TransformComponent>(m_QuadEntity);
  m_ActiveScene->GetRegistry().emplace<SpriteComponent>(m_QuadEntity, m_QuadColor);
}

void Zero::EditorLayer::OnDetach() {
}

void Zero::EditorLayer::OnUpdate(const DeltaTime deltaTime) {
  if (m_IsViewportFocused) {
    m_CameraController.OnUpdate(deltaTime);
  }
  m_ActiveScene->OnUpdate(deltaTime);
}

void Zero::EditorLayer::OnRender() {
  Renderer2D::ResetStats();

  m_Framebuffer->Bind();
  RenderCommand::SetClearColor({ 0.02f, 0.02f, 0.022f, 1.0f });
  RenderCommand::Clear();

  Renderer2D::BeginScene(m_CameraController.GetCamera());
  m_ActiveScene->OnRender();
  Renderer2D::EndScene();

  m_Framebuffer->Unbind();
}

void Zero::EditorLayer::OnUIRender() {
  static bool isOpen{ true };
  static bool isFullscreenPersistant{ true };
  static bool isFullscreen{ isFullscreenPersistant };
  static ImGuiDockNodeFlags dockSpaceFlags{ ImGuiDockNodeFlags_None };
  static ImGuiWindowFlags windowFlags{ ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking };

  SetupDockspace(isFullscreen, windowFlags, dockSpaceFlags);

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

  RenderSettingsPanel();
  RenderViewportPanel();

  ImGui::End();
}

void Zero::EditorLayer::OnEvent(Event& event) {
  m_CameraController.OnEvent(event);
  EventDispatcher dispatcher{ event };
  dispatcher.Dispatch<KeyPressedEvent>(ZR_BIND_FUNCTION(EditorLayer::OnKeyPressed));
}

bool Zero::EditorLayer::OnKeyPressed(KeyPressedEvent& event) {
  if (event.GetKeyCode() == KeyCode::ESCAPE) {
    Application::Get().Close();
    return true;
  }
  return false;
}

void Zero::EditorLayer::RenderViewportPanel() {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
  ImGui::Begin("Viewport");

  m_IsViewportFocused = ImGui::IsWindowFocused();
  m_IsViewportHovered = ImGui::IsWindowHovered();
  Application::Get().GetUILayer()->SetIsBlockingEvents(!m_IsViewportFocused || !m_IsViewportHovered);

  const ImVec2 panelSize{ ImGui::GetContentRegionAvail() };
  const glm::uvec2 viewportPanelSize{ panelSize.x, panelSize.y };
  if (m_ViewportSize != viewportPanelSize && viewportPanelSize.x > 0u && viewportPanelSize.y > 0u) {
    m_Framebuffer->Resize(viewportPanelSize);
    m_ViewportSize = viewportPanelSize;
    m_CameraController.OnResize(viewportPanelSize);
  }

  ImGui::Image(
    m_Framebuffer->GetColorAttachmentRendererID(),
    ImVec2{ static_cast<float>(m_ViewportSize.x), static_cast<float>(m_ViewportSize.y) },
    ImVec2{ 0.0f, 1.0f },
    ImVec2{ 1.0f, 0.0f }
  );
  ImGui::End();
  ImGui::PopStyleVar();
}

void Zero::EditorLayer::RenderSettingsPanel() {
  const RenderStats& stats{ Renderer2D::GetStats() };
  ImGui::Begin("Settings");

  ImGui::Text("Renderer2D Stats");
  ImGui::Text("Draw Calls: %d", stats.DrawCalls);
  ImGui::Text("Quads: %d", stats.QuadCount);
  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

  ImGui::DragFloat("Quad Rotation Speed", &m_RotationSpeed, 0.1f);
  auto& quadColor{ m_ActiveScene->GetRegistry().get<SpriteComponent>(m_QuadEntity).Color };
  ImGui::ColorEdit4("Quad Color", glm::value_ptr(quadColor));

  ImGui::End();
}

void Zero::EditorLayer::SetupDockspace(bool isFullscreen, ImGuiWindowFlags windowFlags, ImGuiDockNodeFlags dockSpaceFlags) {
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
}
