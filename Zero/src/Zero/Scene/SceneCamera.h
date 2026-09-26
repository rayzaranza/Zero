#pragma once
#include "Zero/Camera/Camera.h"

namespace Zero {

class SceneCamera : public Camera {
public:
  SceneCamera();
  virtual ~SceneCamera() = default;
  void SetOrthographic(float size, float nearClip, float farClip);
  void SetViewportSize(const glm::uvec2& size);
  float GetOrthographicSize() const;
  void SetOrthographicSize(const float size);
private:
  void RecalculateProjection();
  float m_OrthographicSize{ 10.0f };
  float m_OrthographicNear{ -1.0f };
  float m_OrthographicFar{ 1.0f };
  float m_AspectRatio{ 0.0f };
};

}
