#pragma once
#include <Zero.h>

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
    Ref<Framebuffer> m_Framebuffer{};
    CameraOrthographicController m_CameraController;
    Ref<Texture2D> m_Texture;
    Ref<Texture2D> m_TextureCheckerboard;
    Array<QuadProperties> m_Quads;
    float m_Rotation{ 0.0f };
    glm::vec2 m_ViewportSize{};
  };
}
