#include "Zero/Camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top)
        : m_Position{ 0.0f }
        , m_ViewMatrix{ 1.0f }
        , m_ProjectionMatrix{ glm::ortho(left, right, bottom, top, -1.0f, 1.0f) }
        , m_Rotation{ 0.0f }
        , m_ViewProjectionMatrix{ m_ProjectionMatrix * m_ViewMatrix }
    {
        ZR_PROFILE_FUNCTION();
    }

    void OrthographicCamera::SetProjectionMatrix(const float left, const float right, const float bottom, const float top)
    {
        ZR_PROFILE_FUNCTION();

        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::CalculateViewProjectionMatrix()
    {
        ZR_PROFILE_FUNCTION();

        glm::mat4 transform{ 1.0f };
        transform = glm::translate(transform, m_Position);
        transform = glm::rotate(transform, m_Rotation, glm::vec3{ 0.0f, 0.0f, 1.0f });
        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        CalculateViewProjectionMatrix();
    }

    void OrthographicCamera::SetRotation(const float rotation)
    {
        m_Rotation = rotation;
        CalculateViewProjectionMatrix();
    }
}
