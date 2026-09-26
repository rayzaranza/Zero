#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>

Zero::SceneCamera::SceneCamera() {
  RecalculateProjection();
}

void Zero::SceneCamera::SetOrthographic(float size, float nearClip, float farClip) {
  m_OrthographicSize = size;
  m_OrthographicNear = nearClip;
  m_OrthographicFar = farClip;
  RecalculateProjection();
}

void Zero::SceneCamera::SetViewportSize(const glm::uvec2& size) {
  m_AspectRatio = static_cast<float>(size.x) / static_cast<float>(size.y);
  RecalculateProjection();
}

float Zero::SceneCamera::GetOrthographicSize() const {
  return m_OrthographicSize;
}

void Zero::SceneCamera::SetOrthographicSize(const float size) {
  m_OrthographicSize = size;
  RecalculateProjection();
}

void Zero::SceneCamera::RecalculateProjection() {
  const float left{ -m_OrthographicSize * m_AspectRatio * 0.5f };
  const float right{ m_OrthographicSize * m_AspectRatio * 0.5f };
  const float bottom{ -m_OrthographicSize * 0.5f };
  const float top{ m_OrthographicSize * 0.5f };
  m_Projection = glm::ortho(left, right, bottom, top, m_OrthographicNear, m_OrthographicFar);
}
