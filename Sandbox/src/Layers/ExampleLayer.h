#pragma once

#include <Zero/Zero.h>

class ExampleLayer : public Zero::Layer
{
  public:
    ExampleLayer();

  public:
    virtual void OnUpdate(Zero::DeltaTime deltaTime) override;
    virtual void OnEvent(Zero::Event& event) override;
    virtual void OnUIRender() override;

  private:
    Zero::ShaderLibraryRef m_ShaderLibrary;

    Zero::ShaderRef m_QuadShader;
    Zero::VertexArrayRef m_QuadVertexArray;
    Zero::Texture2DRef m_Texture;
    Zero::Texture2DRef m_TransparentTexture;

    Zero::OrthographicCameraController m_CameraController;

    Zero::Vector3 m_QuadPosition;
    Zero::Color m_QuadColor;
    Zero::F32 m_QuadMovementSpeed;
};
