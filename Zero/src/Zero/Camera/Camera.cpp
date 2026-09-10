#include "Zero/Camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_Position{ 0.0f }
        , m_ViewMatrix{ 1.0f }
        , m_ProjectionMatrix{ glm::ortho(left, right, bottom, top, -1.0f, 1.0f) }
        , m_Rotation{ 0.0f }
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::CalculateViewProjectionMatrix()
    {
        glm::mat4 transform{ glm::translate({ 1.0f }, m_Position) * glm::rotate({ 1.0f }, glm::radians(m_Rotation), glm::vec3{ 0, 0, 1 }) };
        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        CalculateViewProjectionMatrix();
    }

    void OrthographicCamera::SetRotation(float rotation)
    {
        m_Rotation = rotation;
        CalculateViewProjectionMatrix();
    }

}
