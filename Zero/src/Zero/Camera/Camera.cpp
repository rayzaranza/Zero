#include "Zero/Camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    OrthographicCamera::OrthographicCamera(F32 left, F32 right, F32 bottom, F32 top)
        : m_Position{ 0.0f }
        , m_ViewMatrix{ 1.0f }
        , m_ProjectionMatrix{ glm::ortho(left, right, bottom, top, -1.0f, 1.0f) }
        , m_Rotation{ 0.0f }
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjectionMatrix(F32 left, F32 right, F32 bottom, F32 top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::CalculateViewProjectionMatrix()
    {
        Matrix4 transform{ 1.0f };
        transform = glm::translate(transform, m_Position);
        transform = glm::rotate(transform, glm::radians(m_Rotation), Vector3{ 0, 0, 1 });
        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetPosition(const Vector3& position)
    {
        m_Position = position;
        CalculateViewProjectionMatrix();
    }

    void OrthographicCamera::SetRotation(F32 rotation)
    {
        m_Rotation = rotation;
        CalculateViewProjectionMatrix();
    }

}
