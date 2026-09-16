#pragma once

#include <Zero.h>

class ExampleLayer2D : public Zero::Layer
{
  public:
    ExampleLayer2D();
    ~ExampleLayer2D();

  public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(const Zero::DeltaTime deltaTime) override;
    virtual void OnRender() override;
    virtual void OnUIRender() override;
    virtual void OnEvent(Zero::Event& event) override;

  public:
    bool OnKeyPressed(Zero::KeyPressedEvent& event);

  private:
    Zero::OrthographicCameraController m_CameraController;
    Zero::Texture2DRef m_Texture;
    Zero::Texture2DRef m_TextureB;
    Zero::Array<Zero::Renderer2D::QuadProperties> m_QuadsProperties;
};
