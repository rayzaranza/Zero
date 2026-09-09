#include "Zero/Camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    CameraOrthographic::CameraOrthographic(float left, float right, float bottom, float top)
        : m_Position{0.0f}
        , m_ViewMatrix{1.0f}
        , m_ProjectionMatrix{glm::ortho(left, right, bottom, top, -1.0f, 1.0f)}
        , m_Rotation{0.0f}
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void CameraOrthographic::CalculateViewMatrix()
    {
        glm::mat4 transform{glm::translate({1.0f}, m_Position) * glm::rotate({1.0f}, glm::radians(m_Rotation), glm::vec3{0, 0, 1})};
        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void CameraOrthographic::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        CalculateViewMatrix();
    }

    void CameraOrthographic::SetRotation(float rotation)
    {
        m_Rotation = rotation;
        CalculateViewMatrix();
    }
}
