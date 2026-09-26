#pragma once
#include "Panels/SceneHierarchyPanel.h"
#include <Zero.h>
#include <imgui.h>

namespace Zero {

class EditorLayer : public Layer {
public:
  EditorLayer();
  ~EditorLayer();
public:
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
private:
  CameraOrthographicController m_CameraController;
  Ref<Framebuffer> m_Framebuffer{};
  Ref<Texture2D> m_Texture;
  Ref<Texture2D> m_TextureCheckerboard;
  Array<QuadProps> m_Quads;
  Ref<Scene> m_ActiveScene;
  Entity m_QuadEntity{};
  Entity m_CameraEntityA{};
  Entity m_CameraEntityB{};
  glm::uvec2 m_ViewportSize{ 0u, 0u };
  bool m_IsMainCameraActive{ true };
  float m_Rotation{ 0.0f };
  float m_RotationSpeed{ 1.0f };
  bool m_IsViewportFocused{ false };
  bool m_IsViewportHovered{ false };
  SceneHierarchyPanel m_HierarchyPanel;
};

}
