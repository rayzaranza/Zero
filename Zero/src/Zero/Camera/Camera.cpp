#include "Zero/Camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    OrthographicCamera::OrthographicCamera(const F32 left, const F32 right, const F32 bottom, const F32 top)
        : m_Position{ 0.0f }
        , m_ViewMatrix{ 1.0f }
        , m_ProjectionMatrix{ glm::ortho(left, right, bottom, top, -1.0f, 1.0f) }
        , m_Rotation{ 0.0f }
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjectionMatrix(const F32 left, const F32 right, const F32 bottom, const F32 top)
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

    void OrthographicCamera::SetRotation(const Degrees rotation)
    {
        m_Rotation = rotation;
        CalculateViewProjectionMatrix();
    }
}
