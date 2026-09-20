#pragma once
#include <Zero.h>

class GameLayer : public Zero::Layer {
public:
  GameLayer();
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const Zero::DeltaTime deltaTime) override;
  virtual void OnRender() override;
  virtual void OnUIRender() override;
  virtual void OnEvent(Zero::Event& event) override;
  bool OnKeyPressed(Zero::KeyPressedEvent& event);

private:
  Zero::CameraOrthographicController m_CameraController;
  Zero::Ref<Zero::Texture2D> m_SpriteSheet{};
  Zero::Ref<Zero::SubTexture2D> m_TextureStairs{};
  Zero::Ref<Zero::SubTexture2D> m_TextureBarrel{};
  Zero::Ref<Zero::SubTexture2D> m_TextureTree{};
  static Zero::Map<char, Zero::Ref<Zero::SubTexture2D>> s_TextureMap;
};
