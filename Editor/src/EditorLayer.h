#pragma once
#include "./Panels/SceneHierarchyPanel.h"

#include <Zero.h>
#include <Zero/Camera/EditorCamera.h>


namespace Zero {


class EditorLayer : public Layer
{
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

  private:
    bool OnKeyPressed(KeyPressedEvent& event);
    void RenderViewportPanel();
    void RenderSettingsPanel();
    void NewScene();
    void OpenScene();
    void SaveSceneAs() const;

  private:
    Ref<Framebuffer> m_Framebuffer{};
    EditorCamera m_EditorCamera;
    Ref<Scene> m_ActiveScene;
    glm::uvec2 m_ViewportSize{ 0u, 0u };
    bool m_IsMainCameraActive{ true };
    bool m_IsViewportFocused{ false };
    bool m_IsViewportHovered{ false };
    SceneHierarchyPanel m_SceneHierarchyPanel;
    int16_t m_GizmoType{ -1 };
};


}
