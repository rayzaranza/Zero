#pragma once

#include <Zero/Zero.h>

//======================================================================================
//  Sandbox Example Layer
//======================================================================================
class ExampleLayer : public Zero::Layer
{
  public:
    ExampleLayer();

  public:
    virtual void OnUpdate(Zero::DeltaTime deltaTime) override;
    virtual void OnEvent(Zero::Event& event) override;
    virtual void OnUIRender() override;

  private:
    Zero::Ref<Zero::Shader> m_QuadShader;
    Zero::Ref<Zero::Shader> m_TextureShader;
    Zero::Ref<Zero::VertexArray> m_QuadVertexArray;
    Zero::Ref<Zero::Texture2D> m_Texture;
    Zero::Ref<Zero::Texture2D> m_TransparentTexture;

    Zero::CameraOrthographic m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraMovementSpeed;
    float m_CameraRotationSpeed;
    float m_CameraRotation;

    glm::vec3 m_QuadPosition;
    glm::vec4 m_QuadColor;
    float m_QuadMovementSpeed;
};

//======================================================================================
//  Sandbox Application
//======================================================================================
class Sandbox : public Zero::Application
{
  public:
    Sandbox() { PushLayer(new ExampleLayer()); }
    ~Sandbox() {}
};

//======================================================================================
//  Application Creation
//======================================================================================
Zero::Application* Zero::CreateApplication()
{
    return new Sandbox();
}
