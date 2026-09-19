#pragma once
#include <glm/glm.hpp>

namespace Zero {
  class CameraOrthographic {
  public:
    CameraOrthographic(const float left, const float right, const float bottom = -1.0f, const float top = 1.0f);
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;
    const glm::mat4& GetViewProjectionMatrix() const;
    const glm::vec3& GetPosition() const;
    float GetRotation() const;
    void SetPosition(const glm::vec3& position);
    void SetRotation(const float rotation);
    void SetProjectionMatrix(const float left, const float right, const float bottom, const float top);

  private:
    void CalculateViewProjectionMatrix();
    glm::vec3 m_Position;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewProjectionMatrix;
    float m_Rotation;
  };
}
