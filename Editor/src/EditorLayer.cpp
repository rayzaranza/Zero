#include "EditorLayer.h"
#include <glm/gtc/matrix_transform.hpp>

Zero::EditorLayer::EditorLayer() : Layer{ "EditorLayer" }, m_CameraController{ Application::Get().GetWindow().GetAspectRatio() } {
}

Zero::EditorLayer::~EditorLayer() {
}

void Zero::EditorLayer::OnAttach() {
  m_Texture = Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg");
  m_TextureCheckerboard = Texture2D::Create("D:/Zero/Sandbox/assets/textures/Checkerboard.png");
  m_Framebuffer = Framebuffer::Create({ .Size{ 1280u, 720u } });
  m_ActiveScene = CreateRef<Scene>();
  m_QuadEntity = m_ActiveScene->CreateEntity("Quad");
  m_QuadEntity.AddComponent<SpriteComponent>(glm::vec4{ 0.1f, 1.0f, 0.0f, 1.0f });

  m_CameraEntityA = m_ActiveScene->CreateEntity("Camera A");
  m_CameraEntityA.AddComponent<CameraComponent>();

  m_CameraEntityB = m_ActiveScene->CreateEntity("Camera B");
  CameraComponent& cameraComponentB{ m_CameraEntityB.AddComponent<CameraComponent>() };
  cameraComponentB.IsMain = false;

  RenderCommand::SetClearColor({ 0.02f, 0.02f, 0.022f, 1.0f });

  class CameraController : public ScriptableEntity {
  public:
    void OnCreate() {}

    void OnDestroy() {}

    void OnUpdate(const DeltaTime deltaTime) {
      auto& transform{ GetComponent<TransformComponent>().Transform };
      const float speed{ 5.0f };

      if (Input::IsKeyPressed(KeyCode::A)) {
        transform[3][0] -= speed * deltaTime;
      } else if (Input::IsKeyPressed(KeyCode::D)) {
        transform[3][0] += speed * deltaTime;
      }

      if (Input::IsKeyPressed(KeyCode::W)) {
        transform[3][1] += speed * deltaTime;
      } else if (Input::IsKeyPressed(KeyCode::S)) {
        transform[3][1] -= speed * deltaTime;
      }
    }
  };

  m_CameraEntityA.AddComponent<NativeScriptComponent>().Bind<CameraController>();
}

void Zero::EditorLayer::OnDetach() {
}

void Zero::EditorLayer::OnUpdate(const DeltaTime deltaTime) {
  if (m_ViewportSize.x > 0u && m_ViewportSize.y > 0u && (m_Framebuffer->GetSize().x != m_ViewportSize.x || m_Framebuffer->GetSize().y != m_ViewportSize.y)) {
    m_Framebuffer->Resize(m_ViewportSize);
    m_CameraController.OnResize(m_ViewportSize);
    m_ActiveScene->OnViewportResize(m_ViewportSize);
  }

  m_Rotation += m_RotationSpeed * deltaTime;

  if (m_IsViewportFocused) {
    m_CameraController.OnUpdate(deltaTime);
  }

  m_ActiveScene->OnUpdate(deltaTime);
}

void Zero::EditorLayer::OnRender() {
  Renderer2D::ResetStats();
  m_Framebuffer->Bind();
  RenderCommand::Clear();
  m_ActiveScene->OnRender();
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

  const ImVec2 viewportPanelSize{ ImGui::GetContentRegionAvail() };
  m_ViewportSize = { static_cast<uint32_t>(viewportPanelSize.x), static_cast<uint32_t>(viewportPanelSize.y) };
  ImGui::Image(m_Framebuffer->GetColorAttachmentRendererID(), viewportPanelSize, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
  ImGui::End();
  ImGui::PopStyleVar();
}

void Zero::EditorLayer::RenderSettingsPanel() {
  const RenderStats& stats{ Renderer2D::GetStats() };
  ImGui::Begin("Settings");
  ImGui::BeginGroup();
  ImGui::Text("Render Stats");
  ImGui::Text("Draw Calls: %d", stats.DrawCalls);
  ImGui::Text("Quads: %d", stats.QuadCount);
  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
  ImGui::EndGroup();

  ImGui::Separator();

  ImGui::DragFloat("Quad Rotation Speed", &m_RotationSpeed, 0.1f);

  if (m_QuadEntity) {
    ImGui::Separator();
    ImGui::Text("%s", m_QuadEntity.GetComponent<TagComponent>().Tag.c_str());
    ImGui::ColorEdit4("Quad Color", glm::value_ptr(m_QuadEntity.GetComponent<SpriteComponent>().Color));
    ImGui::Separator();
  }

  ImGui::DragFloat3("Camera Transform", glm::value_ptr(m_CameraEntityA.GetComponent<TransformComponent>().Transform[3]));

  if (ImGui::Checkbox("Camera A", &m_IsMainCameraActive)) {
    m_CameraEntityA.GetComponent<CameraComponent>().IsMain = m_IsMainCameraActive;
    m_CameraEntityB.GetComponent<CameraComponent>().IsMain = !m_IsMainCameraActive;
  }

  SceneCamera& cameraB{ m_CameraEntityB.GetComponent<CameraComponent>().Camera };
  float cameraBSize{ cameraB.GetOrthographicSize() };
  if (ImGui::DragFloat("Camera B Size", &cameraBSize)) {
    cameraB.SetOrthographicSize(cameraBSize);
  }

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
