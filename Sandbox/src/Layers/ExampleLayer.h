#pragma once
#include <Zero.h>

class ExampleLayer : public Zero::Layer {
public:
  ExampleLayer();
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const Zero::DeltaTime deltaTime) override;
  virtual void OnEvent(Zero::Event& event) override;
  virtual void OnRender() override;
  virtual void OnUIRender() override;

private:
  Zero::Ref<Zero::ShaderLibrary> m_ShaderLibrary;
  Zero::Ref<Zero::Shader> m_QuadShader;
  Zero::Ref<Zero::VertexArray> m_QuadVertexArray;
  Zero::Ref<Zero::Texture2D> m_Texture;
  Zero::Ref<Zero::Texture2D> m_TransparentTexture;
  Zero::CameraOrthographicController m_CameraController;
  glm::vec3 m_QuadPosition;
  glm::vec4 m_QuadColor;
  float m_QuadMovementSpeed;
};
