#pragma once
#include "../ParticleSystem.h"
#include <Zero.h>

class ExampleLayer2D : public Zero::Layer {
public:
  ExampleLayer2D();
  ~ExampleLayer2D();
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const Zero::DeltaTime deltaTime) override;
  virtual void OnRender() override;
  virtual void OnUIRender() override;
  virtual void OnEvent(Zero::Event& event) override;
  bool OnKeyPressed(Zero::KeyPressedEvent& event);

private:
  Zero::CameraOrthographicController m_CameraController;
  Zero::Ref<Zero::Texture2D> m_Texture;
  Zero::Ref<Zero::Texture2D> m_TextureB;
  Zero::Array<Zero::QuadProperties> m_Quads;
  float m_Rotation{ 0.0f };
  ParticleProps m_Particle;
  ParticleSystem m_ParticleSystem;
};
