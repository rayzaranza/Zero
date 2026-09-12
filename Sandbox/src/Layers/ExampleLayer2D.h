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
    Zero::Boolean OnKeyPressed(Zero::KeyPressedEvent& event);

  public:
    struct ProfileResult
    {
        Zero::String Name{};
        Zero::Milliseconds Time{};
    };

  private:
    Zero::OrthographicCameraController m_CameraController;
    Zero::Color m_QuadColor;
    Zero::Texture2DRef m_Texture;

    Zero::Array<ProfileResult> m_ProfileResults{};
};
