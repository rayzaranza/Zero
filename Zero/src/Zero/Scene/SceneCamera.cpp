#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>


Zero::SceneCamera::SceneCamera() {
  RecalculateProjection();
}


void Zero::SceneCamera::SetOrthographic(float size, float nearClip, float farClip) {
  m_ProjectionType = ProjectionType::Orthographic;
  m_OrthographicSize = size;
  m_OrthographicNearClip = nearClip;
  m_OrthographicFarClip = farClip;
  RecalculateProjection();
}


void Zero::SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip) {
  m_ProjectionType = ProjectionType::Perspective;
  m_PerspectiveFOV = verticalFOV;
  m_PerspectiveNearClip = nearClip;
  m_PerspectiveFarClip = farClip;
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


float Zero::SceneCamera::GetOrthographicNearClip() const {
  return m_OrthographicNearClip;
}


float Zero::SceneCamera::GetOrthographicFarClip() const {
  return m_OrthographicFarClip;
}


void Zero::SceneCamera::SetOrthographicNearClip(const float nearClip) {
  m_OrthographicNearClip = nearClip;
  RecalculateProjection();
}


void Zero::SceneCamera::SetOrthographicFarClip(const float farClip) {
  m_OrthographicFarClip = farClip;
  RecalculateProjection();
}


void Zero::SceneCamera::RecalculateProjection() {
  if (m_ProjectionType == ProjectionType::Perspective) {
    m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNearClip, m_PerspectiveFarClip);
  } else {
    const float left{ -m_OrthographicSize * m_AspectRatio * 0.5f };
    const float right{ m_OrthographicSize * m_AspectRatio * 0.5f };
    const float bottom{ -m_OrthographicSize * 0.5f };
    const float top{ m_OrthographicSize * 0.5f };
    m_Projection = glm::ortho(left, right, bottom, top, m_OrthographicNearClip, m_OrthographicFarClip);
  }
}


Zero::SceneCamera::ProjectionType Zero::SceneCamera::GetProjectionType() const {
  return m_ProjectionType;
}


void Zero::SceneCamera::SetPerspectiveVerticalFOV(const float perspectiveFOV) {
  m_PerspectiveFOV = perspectiveFOV;
}


float Zero::SceneCamera::GetPerspectiveVerticalFOV() const {
  return m_PerspectiveFOV;
}


void Zero::SceneCamera::SetPerspectiveNearClip(const float nearClip) {
  m_PerspectiveNearClip = nearClip;
}


float Zero::SceneCamera::GetPerspectiveNearClip() const {
  return m_PerspectiveNearClip;
}


void Zero::SceneCamera::SetPerspectiveFarClip(const float nearClip) {
  m_PerspectiveNearClip = nearClip;
}


float Zero::SceneCamera::GetPerspectiveFarClip() const {
  return m_PerspectiveFarClip;
}


void Zero::SceneCamera::SetAspectRatio(const float aspectRatio) {
  m_AspectRatio = aspectRatio;
  RecalculateProjection();
}


float Zero::SceneCamera::GetAspectRatio() const {
  return m_AspectRatio;
}


void Zero::SceneCamera::SetProjectionType(ProjectionType type) {
  m_ProjectionType = type;
  RecalculateProjection();
}
