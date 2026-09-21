#pragma once
#include <Zero.h>
#include <imgui.h>

namespace Zero {

class EditorLayer : public Layer {
public:
  EditorLayer();
  ~EditorLayer();
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const DeltaTime deltaTime) override;
  virtual void OnRender() override;
  virtual void OnUIRender() override;
  virtual void OnEvent(Event& event) override;
  bool OnKeyPressed(KeyPressedEvent& event);

private:
  void RenderViewportPanel();
  void RenderSettingsPanel();
  void SetupDockspace(bool isFullscreen, ImGuiWindowFlags windowFlags, ImGuiDockNodeFlags dockSpaceFlags);
  Ref<Framebuffer> m_Framebuffer{};
  CameraOrthographicController m_CameraController;
  Ref<Texture2D> m_Texture;
  Ref<Texture2D> m_TextureCheckerboard;
  Array<QuadProps> m_Quads;
  float m_Rotation{ 0.0f };
  float m_RotationSpeed{ 1.0f };
  glm::uvec2 m_ViewportSize{};
  bool m_IsViewportFocused{ false };
  bool m_IsViewportHovered{ false };
  Ref<Scene> m_ActiveScene;
  entt::entity m_QuadEntity;
  glm::vec4 m_QuadColor{ 1.0f };
};

}
