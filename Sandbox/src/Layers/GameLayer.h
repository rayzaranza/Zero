#pragma once

#include <Zero.h>

class GameLayer : public Zero::Layer
{
  public:
    GameLayer();

  public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(const Zero::DeltaTime deltaTime) override;
    virtual void OnRender() override;
    virtual void OnUIRender() override;
    virtual void OnEvent(Zero::Event& event) override;

  private:
    Zero::OrthographicCameraController m_CameraController;
    Zero::Texture2DRef m_SpriteSheet;
    Zero::Ref<Zero::SubTexture2D> m_TextureStairs;
    Zero::Ref<Zero::SubTexture2D> m_TextureBarrel;
    Zero::Ref<Zero::SubTexture2D> m_TextureTree;
};
