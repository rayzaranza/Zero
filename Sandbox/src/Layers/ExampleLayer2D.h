#pragma once

#include <Zero/Zero.h>

class ExampleLayer2D : public Zero::Layer
{
  public:
    ExampleLayer2D();
    ~ExampleLayer2D();

  public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Zero::DeltaTime deltaTime) override;
    virtual void OnUIRender() override;
    virtual void OnEvent(Zero::Event& event) override;

  private:
    Zero::Ref<Zero::ShaderLibrary> m_ShaderLibrary;
    Zero::Ref<Zero::VertexArray> m_QuadVertexArray{};
    Zero::OrthographicCameraController m_CameraController;
    glm::vec4 m_QuadColor{ 0.2f, 0.1f, 0.4f, 1.0f };
};
