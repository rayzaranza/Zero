#include "Zero/Camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Zero::Camera::Camera(const glm::mat4& projection) : m_Projection{ projection } {
}

const glm::mat4& Zero::Camera::GetProjection() const {
  return m_Projection;
}

Zero::CameraOrthographic::CameraOrthographic(const float left, const float right, const float bottom, const float top)
  : m_Position{ 0.0f }
  , m_ViewMatrix{ 1.0f }
  , m_ProjectionMatrix{ glm::ortho(left, right, bottom, top, -1.0f, 1.0f) }
  , m_Rotation{ 0.0f }
  , m_ViewProjectionMatrix{ m_ProjectionMatrix * m_ViewMatrix } {
}

const glm::mat4& Zero::CameraOrthographic::GetViewMatrix() const {
  return m_ViewMatrix;
}

const glm::mat4& Zero::CameraOrthographic::GetProjectionMatrix() const {
  return m_ProjectionMatrix;
}

const glm::mat4& Zero::CameraOrthographic::GetViewProjectionMatrix() const {
  return m_ViewProjectionMatrix;
}

const glm::vec3& Zero::CameraOrthographic::GetPosition() const {
  return m_Position;
}

float Zero::CameraOrthographic::GetRotation() const {
  return m_Rotation;
}

void Zero::CameraOrthographic::SetProjectionMatrix(const float left, const float right, const float bottom, const float top) {
  m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
  m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Zero::CameraOrthographic::CalculateViewProjectionMatrix() {
  glm::mat4 transform{ 1.0f };
  transform = glm::translate(transform, m_Position);
  transform = glm::rotate(transform, m_Rotation, glm::vec3{ 0.0f, 0.0f, 1.0f });
  m_ViewMatrix = glm::inverse(transform);
  m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Zero::CameraOrthographic::SetPosition(const glm::vec3& position) {
  m_Position = position;
  CalculateViewProjectionMatrix();
}

void Zero::CameraOrthographic::SetRotation(const float rotation) {
  m_Rotation = rotation;
  CalculateViewProjectionMatrix();
}
